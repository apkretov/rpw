@echo off
REM Usage: squash N "Combined commit message"

setlocal enabledelayedexpansion

set "arg1=%~1"
set "arg2=%~2"

if "%arg1%"=="" (
    echo Please provide the number of commits to squash.
    exit /b 1
)

if "%arg2%"=="" (
    echo Please provide a commit message.
    exit /b 1
)

git add -v .
git reset --soft HEAD~%arg1%
git commit -m "%arg2%"
git log --oneline -3
