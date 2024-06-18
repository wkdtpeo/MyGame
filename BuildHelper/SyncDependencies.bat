@echo off
@rem Jenkins에서 Setup.bat 실행시 Install prerequisites 부분에서 멈추는 현상으로 새로 만듦
@rem UE5 Engine Sync Depenencies (Install prerequisites 제외)
setlocal
pushd "%~dp0"

rem Figure out if we should append the -prompt argument
set PROMPT_ARGUMENT=
for %%P in (%*) do if /I "%%P" == "--prompt" goto no_prompt_argument
for %%P in (%*) do if /I "%%P" == "--force" goto no_prompt_argument
set PROMPT_ARGUMENT=--prompt
:no_prompt_argument

@rem UE5 엔진 절대경로
set ENGINE_DIR=..\Engine
if not exist %ENGINE_DIR% ( 
    echo ENGINE_DIR ERROR! 
    goto error
) 

pushd %ENGINE_DIR%
set ENGINE_DIR=%cd%
echo #ENGINE_DIR : %ENGINE_DIR%
popd

rem Sync the dependencies...
%ENGINE_DIR%\Binaries\DotNET\GitDependencies\win-x64\GitDependencies.exe %PROMPT_ARGUMENT% %*
if %ERRORLEVEL% NEQ 0 goto error

rem Setup the git hooks...
if not exist .git\hooks goto no_git_hooks_directory
echo Registering git hooks...
echo #!/bin/sh >.git\hooks\post-checkout
echo %ENGINE_DIR%/Binaries/DotNET/GitDependencies/win-x64/GitDependencies.exe %* >>.git\hooks\post-checkout
echo #!/bin/sh >.git\hooks\post-merge
echo %ENGINE_DIR%/Binaries/DotNET/GitDependencies/win-x64/GitDependencies.exe %* >>.git\hooks\post-merge
:no_git_hooks_directory

rem Done!
goto :end

rem Error happened. Wait for a keypress before quitting.
:error
pause

:end
popd