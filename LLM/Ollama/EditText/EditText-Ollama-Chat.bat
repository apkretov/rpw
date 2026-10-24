@echo off
title Ollama text editor (chat)
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0edit-text-ollama.ps1" -Keep
