@echo off
REM Usage: squash "Combined commit message"

setlocal enabledelayedexpansion

set "commit_msg=%~1"

if "%commit_msg%"=="" (
    echo Please provide a commit message.
    exit /b 1
)

git add -v .
git reset --soft HEAD~1
git commit -m "%commit_msg%"
if errorlevel 1 (
    echo Commit failed.
    exit /b 1
)

git log --oneline -3

for /f "delims=" %%i in ('git -C "%~dp0." log -1 --format^="%%h %%s" 2^>nul') do echo|set /p="%%i"| clip