@echo off
REM Usage: commit "Commit message with spaces"

setlocal enabledelayedexpansion

set "arg1=%~1"

if "%arg1%"=="" (
    echo Please provide a commit message.
    exit /b 1
)

git add -v .
git commit -m "%arg1%"
git log --oneline -3