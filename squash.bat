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
git log --oneline -3