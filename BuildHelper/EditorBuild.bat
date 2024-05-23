@echo off
@rem UE5 Editor Build

echo =========================================
echo EditorBuild
echo =========================================
echo Run %~nx0
echo Current Directory: %CD%

echo =========================================
echo Check UnrealEngine GitDependencies...
echo =========================================
setlocal
pushd %~dp0

@rem Sync the dependencies...
..\Engine\Binaries\DotNET\GitDependencies\win-x64\GitDependencies.exe %*
if ERRORLEVEL 1 goto error

@rem Setup the git hooks...
if not exist .git\hooks goto no_git_hooks_directory
echo Registering git hooks...
echo #!/bin/sh >.git\hooks\post-checkout
echo Engine/Binaries/DotNET/GitDependencies/win-x64/GitDependencies.exe %* >>.git\hooks\post-checkout
echo #!/bin/sh >.git\hooks\post-merge
echo Engine/Binaries/DotNET/GitDependencies/win-x64/GitDependencies.exe %* >>.git\hooks\post-merge
:no_git_hooks_directory

@rem Done!
goto DONE

@rem Error happened. Wait for a keypress before quitting.
:error
echo %~nx0 Failed GitDependencies...

:DONE
popd