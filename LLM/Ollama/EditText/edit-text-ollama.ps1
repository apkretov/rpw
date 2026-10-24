# Edit clipboard text with Ollama (default model qwen3:8b-nothink): rewrites text written by a
# non-native speaker into proper native English. Ollama counterpart of ..\EditText (COLIBRI).
#   EditText-Ollama.bat       one-shot: starts Ollama if needed, edits, copies the answer, then
#                             unloads the model (only if this run loaded it) to free memory.
#   EditText-Ollama-Chat.bat  same script with -Keep: keeps the conversation and the model loaded
#                             and lets you ask follow-ups. At the prompt:
#                               <text>    follow-up question/request about the last answer
#                               N         edit the new clipboard text (starts a new conversation)
#                               Q / Enter quit, the model stays loaded (Ollama's normal keep-alive)
#                               S         quit and unload the model
#                             Every answer is copied to the clipboard.
# The instruction prepended to your text lives in edit-instruction.txt (same folder). It is an exact
# copy of ..\EditText\edit-instruction.txt; do not change its wording without the owner's approval.
#
# Parameters (all optional):
#   -Text <string>        edit this text instead of the clipboard text
#   -Model <name>         Ollama model (default qwen3:8b-nothink; qwen3:4b-instruct is faster, weaker)
#   -Temperature <num>    sampling temperature (default 0 = deterministic). In tests (Oct 2026) the
#                         "Concise version / Full edited version" format was followed in every
#                         run at 0, so 0 is kept. Note: already-correct text still gets two
#                         lightly reworded versions instead of "No changes needed." (same at 0.6).
#   -Keep                 chat mode (see above)
#   -NoPause              do not wait for Enter at the end (for scripted use)
#
# Exit codes: 0 = OK, 1 = empty clipboard or error, 2 = the answer contains broken characters (U+FFFD).
#
# Design choices:
# - ONE user message: instruction + newline + text, no system message. In past tests, rules put in a
#   system message made this model family edit the rules instead of the text.
# - The 'think' request parameter is NOT sent (the custom no-think template may reject it), but any
#   <think>...</think> block in the answer is still stripped.
# - Context: the server default (OLLAMA_CONTEXT_LENGTH) is 4096 tokens. options.num_ctx is estimated
#   per request as (instruction + conversation chars) / 2.5 tokens x 3 (room for the prompt plus the
#   two rewritten versions), rounded up to 1024, minimum 4096, capped at 16384. VRAM is only 4 GB,
#   so it is never set larger than needed. In chat mode it never shrinks within a session, because
#   a different num_ctx makes Ollama reload the model.
# - One-shot mode checks /api/ps before the first request; only if the model was not loaded does the
#   request carry keep_alive = 0 (and the finally block makes sure it is unloaded even after an error).
#   Chat-mode requests never use keep_alive 0; S unloads with POST /api/generate {model, keep_alive: 0}.
# - Text is UTF-8 end to end; any U+FFFD in an answer is reported (exit code 2).
param(
    [string]$Text,
    [string]$Model = 'qwen3:8b-nothink',
    [double]$Temperature = 0,
    [switch]$Keep,
    [switch]$NoPause
)
$ErrorActionPreference = 'Stop'
$base = 'http://127.0.0.1:11434'
$ollama = Join-Path $env:LOCALAPPDATA 'Programs\Ollama\ollama.exe'
$Replacement = [char]0xFFFD
$MinCtx = 4096; $MaxCtx = 16384
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
function Get-ClipText {
    $t = Get-Clipboard -Raw
    if ([string]::IsNullOrWhiteSpace($t)) { return $null }
    return $t.Trim()
}
function Get-NumCtx($messages) {
    # ~2.5 chars per token for the prompt, x3 for prompt + answer (two rewritten versions).
    $chars = 0; foreach ($m in $messages) { $chars += $m.content.Length }
    $need = [int][Math]::Ceiling($chars / 2.5 * 3)
    $need = [int]([Math]::Ceiling($need / 1024) * 1024)
    return [Math]::Min($MaxCtx, [Math]::Max($MinCtx, $need))
}
function Get-ErrorBody([Net.WebException]$e) {
    $r = $e.Response
    if (-not $r) { return $e.Message }
    try { return (New-Object IO.StreamReader($r.GetResponseStream(), [Text.Encoding]::UTF8)).ReadToEnd() } catch { return $e.Message }
}
function Invoke-OllamaPost([string]$path, $body) {
    $json = $body | ConvertTo-Json -Depth 6
    $req = [Net.HttpWebRequest]::Create("$base$path")
    $req.Method = 'POST'; $req.ContentType = 'application/json; charset=utf-8'
    $req.Timeout = [Threading.Timeout]::Infinite; $req.ReadWriteTimeout = [Threading.Timeout]::Infinite
    $bytes = [Text.Encoding]::UTF8.GetBytes($json)
    $s = $req.GetRequestStream(); $s.Write($bytes, 0, $bytes.Length); $s.Close()
    try { return $req.GetResponse() } catch [Net.WebException] { throw "Ollama: $(Get-ErrorBody $_.Exception)" }
}
function Stop-Model {
    Write-Host "`nUnloading $Model to free memory..." -ForegroundColor DarkGray
    try {
        $resp = Invoke-OllamaPost '/api/generate' @{ model = $Model; keep_alive = 0 }
        $resp.Close()
    } catch { Write-Host "Could not unload the model: $($_.Exception.Message)" -ForegroundColor Yellow }
}
function Send-Chat($messages, [bool]$unloadAfter) {
    $script:numCtx = [Math]::Max($script:numCtx, (Get-NumCtx $messages))
    $body = @{ model = $Model; messages = @($messages); stream = $true
               options = @{ temperature = $Temperature; num_ctx = $script:numCtx } }
    if ($unloadAfter) { $body.keep_alive = 0 }
    $resp = Invoke-OllamaPost '/api/chat' $body
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
    $ans = [regex]::Replace($sb.ToString(), '(?s)<think>.*?</think>', '')
    $ans = [regex]::Replace($ans, '(?s)^\s*<think>.*$', '')   # unterminated think block
    $ans = $ans.Trim()
    Write-Host ("`n`n[{0:N0} s]" -f $sw.Elapsed.TotalSeconds) -ForegroundColor DarkGray
    if ([string]::IsNullOrWhiteSpace($ans)) { throw 'The model returned an empty answer.' }
    return $ans
}
function Publish-Answer([string]$ans) {
    Set-Clipboard -Value $ans
    $bad = Get-BrokenCount $ans
    if ($bad -gt 0) {
        Write-Host "Warning: the model produced $bad broken character(s), shown as a box or '?'. Fix those words by hand." -ForegroundColor Yellow
        $script:exitCode = 2
    }
    Write-Host 'The answer is copied to the clipboard.' -ForegroundColor DarkGray
}

$instrFile = Join-Path $PSScriptRoot 'edit-instruction.txt'
$instr = (Get-Content -Raw -Encoding UTF8 $instrFile).Trim()
if ($PSBoundParameters.ContainsKey('Text')) {
    $Text = if ([string]::IsNullOrWhiteSpace($Text)) { $null } else { $Text.Trim() }
} else { $Text = Get-ClipText }
if (-not $Text) { Write-Host 'The clipboard has no text. Copy the text you want edited, then run this again.' -ForegroundColor Yellow; Exit-Script 1 }

$script:exitCode = 0
$script:numCtx = $MinCtx
$unloadAfter = $false
$quitNoPause = $false
try {
    if (-not (Test-Server)) {
        if (-not (Test-Path $ollama)) { throw "Ollama is not running and $ollama was not found." }
        Write-Host 'Starting Ollama...' -ForegroundColor Cyan
        Start-Process -FilePath $ollama -ArgumentList 'serve' -WindowStyle Hidden | Out-Null
        $deadline = (Get-Date).AddMinutes(2)
        while (-not (Test-Server)) {
            if ((Get-Date) -gt $deadline) { throw 'Ollama did not start within 2 minutes.' }
            Start-Sleep -Seconds 1; Write-Host '.' -NoNewline
        }
        Write-Host ''
    }
    $wasLoaded = Test-ModelLoaded
    if (-not $wasLoaded) { Write-Host "Loading $Model..." -ForegroundColor Cyan }
    # One-shot: unload after the request only if this run is the one loading the model,
    # so a model you are already using elsewhere stays loaded.
    $unloadAfter = (-not $Keep) -and (-not $wasLoaded)

    $messages = New-Object System.Collections.ArrayList
    $chatDone = $false
    while (-not $chatDone) {
        [void]$messages.Add(@{ role = 'user'; content = "$instr`n$Text" })
        Write-Host "`n--- Text sent ($($Text.Length) chars) ---" -ForegroundColor DarkGray
        Write-Host "`n--- $Model ---" -ForegroundColor Green
        $answer = Send-Chat $messages $unloadAfter
        [void]$messages.Add(@{ role = 'assistant'; content = $answer })
        Publish-Answer $answer
        if (-not $Keep) {
            if ($unloadAfter) { Write-Host 'The model is unloaded to free memory.' -ForegroundColor DarkGray }
            break
        }

        $next = $false
        while (-not $next) {
            Write-Host "`nType a follow-up and press Enter. N = edit new clipboard text, Q = quit (model stays loaded), S = quit and unload." -ForegroundColor Cyan
            $f = Read-Host '>'
            if ($null -eq $f) { $f = '' }                       # end of redirected input = quit
            switch -Regex ($f.Trim()) {
                '^(q|)$' { Write-Host "$Model stays loaded; run EditText-Ollama-Chat.bat or EditText-Ollama.bat again for instant start."; $next = $true; $chatDone = $true; $quitNoPause = $true }
                '^s$'    { Stop-Model; $next = $true; $chatDone = $true; $quitNoPause = $true }
                '^n$'    {
                    $t = Get-ClipText
                    if (-not $t) { Write-Host 'The clipboard has no text.' -ForegroundColor Yellow; continue }
                    $Text = $t; $messages.Clear(); $next = $true
                }
                default  {
                    [void]$messages.Add(@{ role = 'user'; content = $f.Trim() })
                    Write-Host "`n--- $Model ---" -ForegroundColor Green
                    try {
                        $a = Send-Chat $messages $false
                        [void]$messages.Add(@{ role = 'assistant'; content = $a })
                        Publish-Answer $a
                    } catch {
                        $messages.RemoveAt($messages.Count - 1)
                        Write-Host "Request failed: $($_.Exception.Message)" -ForegroundColor Red
                    }
                }
            }
        }
    }
} catch {
    Write-Host "Editing failed: $($_.Exception.Message)" -ForegroundColor Red
    $script:exitCode = 1
} finally {
    # One-shot runs that loaded the model must leave it unloaded, even after an error or Ctrl+C.
    if ($unloadAfter -and (Test-ModelLoaded)) { Stop-Model }
}
if ($quitNoPause) { exit $script:exitCode }   # Q/S in chat mode close at once, like EditText-Chat.bat
Exit-Script $script:exitCode
