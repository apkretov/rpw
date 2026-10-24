# Translate clipboard text from English into Russian with COLIBRI (Qwen3.6-35B-A3B, CPU backend).
#   TranslateText.bat  one-shot: loads the model if needed, translates, copies the answer, unloads.
# The instruction prepended to your text lives in translate-instruction.txt (same folder).
#
# Broken characters: all text is UTF-8 end to end, but this COLIBRI build sometimes generates
# incomplete Cyrillic byte sequences (a model/engine issue, reproducible at any temperature),
# which the server turns into U+FFFD (shown as a box or "?"). The script cannot recover those
# letters, so it counts them and warns, and exits with code 2 when any are present.
#
# Parameters (all optional):
#   -Text <string>   translate this text instead of the clipboard text
#   -NoPause         do not wait for Enter at the end (for scripted use)
param(
    [string]$Text,
    [double]$Temperature = 0,
    [switch]$NoPause
)
$ErrorActionPreference = 'Stop'
$root = 'C:\Users\Alexander\colibri'
$base = 'http://127.0.0.1:8000'
$py   = "$root\venv\Scripts\python.exe"
$Replacement = [char]0xFFFD
try { [Console]::OutputEncoding = [Text.Encoding]::UTF8 } catch {}
$env:MSYS2_ROOT      = "$root\tools\msys64"
$env:COLI_SETUP_HOME = "$root\setup-home"
$env:COLI_ENGINE     = "$root\repo\c\qwen36.exe"

function Exit-Script([int]$code) {
    if (-not $NoPause) { Read-Host "`nPress Enter to close" | Out-Null }
    exit $code
}
function Test-Server {
    try { return ((Invoke-RestMethod "$base/health" -TimeoutSec 2).status -eq 'ok') } catch { return $false }
}
function Stop-Colibri {
    Write-Host "`nUnloading COLIBRI to free RAM..." -ForegroundColor DarkGray
    Push-Location "$root\repo\c"; try { & $py coli stop | Out-Null } catch {} finally { Pop-Location }
}
function Get-BrokenCount([string]$s) { return ($s.ToCharArray() | Where-Object { $_ -eq $Replacement }).Count }
function Send-Chat($messages, [double]$temp) {
    $body = @{ model = $script:modelId; messages = $messages; stream = $true; temperature = $temp } | ConvertTo-Json -Depth 6
    $req = [Net.HttpWebRequest]::Create("$base/v1/chat/completions")
    $req.Method = 'POST'; $req.ContentType = 'application/json; charset=utf-8'
    $req.Timeout = [Threading.Timeout]::Infinite; $req.ReadWriteTimeout = [Threading.Timeout]::Infinite
    $bytes = [Text.Encoding]::UTF8.GetBytes($body)
    $s = $req.GetRequestStream(); $s.Write($bytes, 0, $bytes.Length); $s.Close()
    $resp = $req.GetResponse()
    $sr = New-Object IO.StreamReader($resp.GetResponseStream(), [Text.Encoding]::UTF8)
    $sb = New-Object Text.StringBuilder
    $sw = [Diagnostics.Stopwatch]::StartNew()
    try {
        while ($null -ne ($line = $sr.ReadLine())) {
            if (-not $line.StartsWith('data:')) { continue }
            $d = $line.Substring(5).Trim()
            if ($d -eq '[DONE]') { break }
            try { $j = $d | ConvertFrom-Json } catch { continue }
            $c = $j.choices[0].delta.content
            if ($c) { Write-Host $c -NoNewline; [void]$sb.Append($c) }
        }
    } finally { $sr.Close(); $resp.Close() }
    $ans = ([regex]::Replace($sb.ToString(), '(?s)<think>.*?</think>', '')).Trim()
    Write-Host ("`n`n[{0:N0} s]" -f $sw.Elapsed.TotalSeconds) -ForegroundColor DarkGray
    return $ans
}

$instrFile = Join-Path $PSScriptRoot 'translate-instruction.txt'
$instr = (Get-Content -Raw -Encoding UTF8 $instrFile).Trim()
if (-not $PSBoundParameters.ContainsKey('Text')) { $Text = Get-Clipboard -Raw }
if ([string]::IsNullOrWhiteSpace($Text)) { Write-Host 'The clipboard has no text. Copy the text you want translated, then run this again.' -ForegroundColor Yellow; Exit-Script 1 }
$Text = $Text.Trim()

$startedHere = $false
$exitCode = 0
try {
    if (-not (Test-Server)) {
        Write-Host 'Loading COLIBRI (Qwen3.6-35B-A3B)... this takes a while on first start.' -ForegroundColor Cyan
        $log = Join-Path $env:TEMP 'colibri-serve.log'
        $proc = Start-Process -FilePath $py -WorkingDirectory "$root\repo\c" -WindowStyle Hidden -PassThru `
            -RedirectStandardOutput $log -RedirectStandardError "$log.err" `
            -ArgumentList @('coli','serve','--model',"$root\models\qwen36-35b",'--gpu','none','--auto-tier','--no-think')
        $startedHere = $true
        $deadline = (Get-Date).AddMinutes(20)
        while (-not (Test-Server)) {
            if ($proc.HasExited) { Write-Host 'COLIBRI failed to start. Log:' -ForegroundColor Red; Get-Content "$log.err" -Tail 25; throw 'COLIBRI failed to start.' }
            if ((Get-Date) -gt $deadline) { throw 'COLIBRI did not become ready in 20 minutes.' }
            Start-Sleep -Seconds 3; Write-Host '.' -NoNewline
        }
        Write-Host ''
    }
    $script:modelId = 'default'
    try { $script:modelId = (Invoke-RestMethod "$base/v1/models" -TimeoutSec 5).data[0].id } catch {}

    $messages = @( @{ role = 'user'; content = "$instr`n$Text" } )
    Write-Host "`n--- Text sent ($($Text.Length) chars) ---" -ForegroundColor DarkGray
    Write-Host "`n--- COLIBRI ---" -ForegroundColor Green
    $answer = Send-Chat $messages $Temperature
    Set-Clipboard -Value $answer
    $bad = Get-BrokenCount $answer
    if ($bad -gt 0) {
        Write-Host "Warning: the model produced $bad broken character(s), shown as a box or '?'. Fix those words by hand." -ForegroundColor Yellow
        $exitCode = 2
    }
    Write-Host 'The translation is copied to the clipboard.' -ForegroundColor DarkGray
} catch {
    Write-Host "Translation failed: $($_.Exception.Message)" -ForegroundColor Red
    $exitCode = 1
} finally {
    if ($startedHere) { Stop-Colibri }
}
Exit-Script $exitCode