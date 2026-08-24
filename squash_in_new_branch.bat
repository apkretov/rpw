@echo off
REM Usage: ./squash_in_new_branch.bat BRANCH_NAME NUM_COMMITS "Commit Message"

setlocal enabledelayedexpansion

set "BRANCH_NAME=%~1"
set "NUM_COMMITS=%~2"
set "COMMIT_MSG=%~3"

:: Validation
if "%BRANCH_NAME%"=="" (
    echo Error: Please provide a new branch name.
    exit /b 1
)

if "%NUM_COMMITS%"=="" (
    echo Error: Please provide the number of commits to squash.
    exit /b 1
)

if "%COMMIT_MSG%"=="" (
    echo Error: Please provide a squash commit message.
    exit /b 1
)

:: Step 1: Switch to the new branch
REM echo Creating and switching to branch: %BRANCH_NAME%
git switch -c %BRANCH_NAME%
if %errorlevel% neq 0 (
    echo Error: Failed to create branch '%BRANCH_NAME%'. Aborting.
    exit /b %errorlevel%
)

:: Step 2: Stage and Squash
REM echo Staging current changes...
git add -v .

REM echo Squashing the last %NUM_COMMITS% commits...
git reset --soft HEAD~%NUM_COMMITS%
if %errorlevel% neq 0 (
    echo Error: Git reset failed. Check if HEAD~%NUM_COMMITS% exists.
    exit /b %errorlevel%
)

:: Step 3: Commit
REM echo Committing squashed changes...
git commit -m "%COMMIT_MSG%"
if errorlevel 1 (
    echo Commit failed.
    exit /b 1
)

git log --oneline -3

for /f "delims=" %%i in ('git -C "%~dp0." log -1 --format^="%%h %%s" 2^>nul') do echo|set /p="%%i"| clip

REM echo Done successfully!
endlocal