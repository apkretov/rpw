# Translate clipboard text from English into Russian with Ollama (default model qwen3:8b-nothink).
#   TranslateText-Ollama.bat  one-shot: starts Ollama if needed, translates, copies the answer,
#                             then unloads the model (if this run loaded it) to free memory.
# The instruction prepended to your text lives in translate-instruction.txt (same folder).
# This is the Ollama counterpart of ..\TranslateText (COLIBRI), whose build garbles some
# Cyrillic letters. Text is UTF-8 end to end; any U+FFFD in the answer is still reported.
#
# Parameters (all optional):
#   -Text <string>   translate this text instead of the clipboard text
#   -Model <name>    Ollama model to use (default qwen3:8b-nothink; qwen3:4b-instruct is faster)
#   -NoPause         do not wait for Enter at the end (for scripted use)
param(
    [string]$Text,
    [string]$Model = 'qwen3:8b-nothink',
    [double]$Temperature = 0,
    [switch]$NoPause
)
$ErrorActionPreference = 'Stop'
$base = 'http://127.0.0.1:11434'
$ollama = Join-Path $env:LOCALAPPDATA 'Programs\Ollama\ollama.exe'
$Replacement = [char]0xFFFD
try { [Console]::OutputEncoding = [Text.Encoding]::UTF8 } catch {}

function Exit-Script([int]$code) {
    if (-not $NoPause) { Read-Host "`nPress Enter to close" | Out-Null }
    exit $code
}
function Test-Server {
    try { Invoke-RestMethod "$base/api/version" -TimeoutSec 2 | Out-Null; return $true } catch { return $false }
}
function Test-ModelLoaded {
    try { return [bool]((Invoke-RestMethod "$base/api/ps" -TimeoutSec 5).models | Where-Object { $_.name -eq $Model -or $_.model -eq $Model }) } catch { return $false }
}
function Get-BrokenCount([string]$s) { return ($s.ToCharArray() | Where-Object { $_ -eq $Replacement }).Count }
function Send-Chat($messages, [bool]$unloadAfter) {
    $body = @{ model = $Model; messages = $messages; stream = $true; options = @{ temperature = $Temperature } }
    if ($unloadAfter) { $body.keep_alive = 0 }
    $json = $body | ConvertTo-Json -Depth 6
    $req = [Net.HttpWebRequest]::Create("$base/api/chat")
    $req.Method = 'POST'; $req.ContentType = 'application/json; charset=utf-8'
    $req.Timeout = [Threading.Timeout]::Infinite; $req.ReadWriteTimeout = [Threading.Timeout]::Infinite
    $bytes = [Text.Encoding]::UTF8.GetBytes($json)
    $s = $req.GetRequestStream(); $s.Write($bytes, 0, $bytes.Length); $s.Close()
    try { $resp = $req.GetResponse() } catch [Net.WebException] {
        $r = $_.Exception.Response
        if ($r) { $msg = (New-Object IO.StreamReader($r.GetResponseStream(), [Text.Encoding]::UTF8)).ReadToEnd(); throw "Ollama: $msg" }
        throw
    }
    $sr = New-Object IO.StreamReader($resp.GetResponseStream(), [Text.Encoding]::UTF8)
    $sb = New-Object Text.StringBuilder
    $sw = [Diagnostics.Stopwatch]::StartNew()
    try {
        while ($null -ne ($line = $sr.ReadLine())) {          # Ollama streams one JSON object per line
            if ([string]::IsNullOrWhiteSpace($line)) { continue }
            $j = $line | ConvertFrom-Json
            if ($j.error) { throw "Ollama: $($j.error)" }
            $c = $j.message.content
            if ($c) { Write-Host $c -NoNewline; [void]$sb.Append($c) }
            if ($j.done) { break }
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

$exitCode = 0
try {
    if (-not (Test-Server)) {
        if (-not (Test-Path $ollama)) { throw "Ollama is not running and $ollama was not found." }
        Write-Host 'Starting Ollama...' -ForegroundColor Cyan
        Start-Process -FilePath $ollama -ArgumentList 'serve' -WindowStyle Hidden | Out-Null
        $deadline = (Get-Date).AddMinutes(2)
        while (-not (Test-Server)) {
            if ((Get-Date) -gt $deadline) { throw 'Ollama did not start within 2 minutes.' }
            Start-Sleep -Seconds 1
        }
    }
    # Unload after this request only if this run is the one loading the model,
    # so a model you are already using elsewhere stays loaded.
    $unloadAfter = -not (Test-ModelLoaded)
    if ($unloadAfter) { Write-Host "Loading $Model..." -ForegroundColor Cyan }

    $messages = @( @{ role = 'user'; content = "$instr`n$Text" } )
    Write-Host "`n--- Text sent ($($Text.Length) chars) ---" -ForegroundColor DarkGray
    Write-Host "`n--- $Model ---" -ForegroundColor Green
    $answer = Send-Chat $messages $unloadAfter
    if ([string]::IsNullOrWhiteSpace($answer)) { throw 'The model returned an empty answer.' }
    Set-Clipboard -Value $answer
    $bad = Get-BrokenCount $answer
    if ($bad -gt 0) {
        Write-Host "Warning: the model produced $bad broken character(s), shown as a box or '?'. Fix those words by hand." -ForegroundColor Yellow
        $exitCode = 2
    }
    Write-Host 'The translation is copied to the clipboard.' -ForegroundColor DarkGray
    if ($unloadAfter) { Write-Host 'The model is unloaded to free memory.' -ForegroundColor DarkGray }
} catch {
    Write-Host "Translation failed: $($_.Exception.Message)" -ForegroundColor Red
    $exitCode = 1
}
Exit-Script $exitCode