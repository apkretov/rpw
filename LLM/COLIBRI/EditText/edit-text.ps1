# Edit clipboard text with COLIBRI (Qwen3.6-35B-A3B, CPU backend).
#   EditText.bat       one-shot: loads the model if needed, edits, copies the answer, unloads.
#   EditText-Chat.bat  keeps the model loaded and lets you ask follow-ups.
# The instruction prepended to your text lives in edit-instruction.txt (same folder).
param([switch]$Keep)
$ErrorActionPreference = 'Stop'
$root = 'C:\Users\Alexander\colibri'
$base = 'http://127.0.0.1:8000'
$py   = "$root\venv\Scripts\python.exe"
try { [Console]::OutputEncoding = [Text.Encoding]::UTF8 } catch {}
$env:MSYS2_ROOT      = "$root\tools\msys64"
$env:COLI_SETUP_HOME = "$root\setup-home"
$env:COLI_ENGINE     = "$root\repo\c\qwen36.exe"

function Test-Server {
    try { return ((Invoke-RestMethod "$base/health" -TimeoutSec 2).status -eq 'ok') } catch { return $false }
}
function Stop-Colibri {
    Write-Host "`nUnloading COLIBRI to free RAM..." -ForegroundColor DarkGray
    Push-Location "$root\repo\c"; try { & $py coli stop | Out-Null } catch {} finally { Pop-Location }
}
function Get-ClipText {
    $t = Get-Clipboard -Raw
    if ([string]::IsNullOrWhiteSpace($t)) { return $null }
    return $t.Trim()
}
function Send-Chat($messages) {
    $body = @{ model = $script:modelId; messages = $messages; stream = $true } | ConvertTo-Json -Depth 6
    $req = [Net.HttpWebRequest]::Create("$base/v1/chat/completions")
    $req.Method = 'POST'; $req.ContentType = 'application/json; charset=utf-8'
    $req.Timeout = [Threading.Timeout]::Infinite; $req.ReadWriteTimeout = [Threading.Timeout]::Infinite
    $bytes = [Text.Encoding]::UTF8.GetBytes($body)
    $s = $req.GetRequestStream(); $s.Write($bytes, 0, $bytes.Length); $s.Close()
    $resp = $req.GetResponse()
    $sr = New-Object IO.StreamReader($resp.GetResponseStream(), [Text.Encoding]::UTF8)
    $sb = New-Object Text.StringBuilder
    $sw = [Diagnostics.Stopwatch]::StartNew()
    while ($null -ne ($line = $sr.ReadLine())) {
        if (-not $line.StartsWith('data:')) { continue }
        $d = $line.Substring(5).Trim()
        if ($d -eq '[DONE]') { break }
        try { $j = $d | ConvertFrom-Json } catch { continue }
        $c = $j.choices[0].delta.content
        if ($c) { Write-Host $c -NoNewline; [void]$sb.Append($c) }
    }
    $sr.Close(); $resp.Close()
    $ans = ([regex]::Replace($sb.ToString(), '(?s)<think>.*?</think>', '')).Trim()
    Write-Host ("`n`n[{0:N0} s]" -f $sw.Elapsed.TotalSeconds) -ForegroundColor DarkGray
    return $ans
}

$instrFile = Join-Path $PSScriptRoot 'edit-instruction.txt'
$instr = (Get-Content -Raw -Encoding UTF8 $instrFile).Trim()
$text = Get-ClipText
if (-not $text) { Write-Host 'The clipboard has no text. Copy the text you want edited, then run this again.' -ForegroundColor Yellow; Read-Host 'Press Enter to close' | Out-Null; exit 1 }

$startedHere = $false
if (-not (Test-Server)) {
    Write-Host 'Loading COLIBRI (Qwen3.6-35B-A3B)... this takes a while on first start.' -ForegroundColor Cyan
    $log = Join-Path $env:TEMP 'colibri-serve.log'
    $proc = Start-Process -FilePath $py -WorkingDirectory "$root\repo\c" -WindowStyle Hidden -PassThru `
        -RedirectStandardOutput $log -RedirectStandardError "$log.err" `
        -ArgumentList @('coli','serve','--model',"$root\models\qwen36-35b",'--gpu','none','--auto-tier','--no-think')
    $startedHere = $true
    $deadline = (Get-Date).AddMinutes(20)
    while (-not (Test-Server)) {
        if ($proc.HasExited) { Write-Host "COLIBRI failed to start. Log:" -ForegroundColor Red; Get-Content "$log.err" -Tail 25; Read-Host 'Press Enter to close' | Out-Null; exit 1 }
        if ((Get-Date) -gt $deadline) { Write-Host 'COLIBRI did not become ready in 20 minutes.' -ForegroundColor Red; Stop-Colibri; Read-Host 'Press Enter to close' | Out-Null; exit 1 }
        Start-Sleep -Seconds 3; Write-Host '.' -NoNewline
    }
    Write-Host ''
}
$script:modelId = 'default'
try { $script:modelId = (Invoke-RestMethod "$base/v1/models" -TimeoutSec 5).data[0].id } catch {}

$messages = New-Object System.Collections.ArrayList
while ($true) {
    $prompt = "$instr`n$text"
    [void]$messages.Add(@{ role = 'user'; content = $prompt })
    Write-Host "`n--- Text sent ($($text.Length) chars) ---" -ForegroundColor DarkGray
    Write-Host "`n--- COLIBRI ---" -ForegroundColor Green
    $answer = Send-Chat $messages
    [void]$messages.Add(@{ role = 'assistant'; content = $answer })
    Set-Clipboard -Value $answer
    Write-Host 'The answer is copied to the clipboard.' -ForegroundColor DarkGray
    if (-not $Keep) { break }

    $next = $false
    while (-not $next) {
        Write-Host "`nType a follow-up and press Enter. N = edit new clipboard text, Q = quit (model stays loaded), S = quit and unload." -ForegroundColor Cyan
        $f = Read-Host '>'
        switch -Regex ($f.Trim()) {
            '^(q|)$' { Write-Host 'COLIBRI stays loaded; run EditText-Chat.bat or EditText.bat again for instant start.'; exit 0 }
            '^s$'    { Stop-Colibri; exit 0 }
            '^n$'    {
                $t = Get-ClipText
                if (-not $t) { Write-Host 'The clipboard has no text.' -ForegroundColor Yellow; continue }
                $text = $t; $messages.Clear(); $next = $true
            }
            default  {
                [void]$messages.Add(@{ role = 'user'; content = $f })
                Write-Host "`n--- COLIBRI ---" -ForegroundColor Green
                $a = Send-Chat $messages
                [void]$messages.Add(@{ role = 'assistant'; content = $a })
                Set-Clipboard -Value $a
                Write-Host 'The answer is copied to the clipboard.' -ForegroundColor DarkGray
            }
        }
    }
}

if ($startedHere) { Stop-Colibri }
Read-Host "`nPress Enter to close" | Out-Null
