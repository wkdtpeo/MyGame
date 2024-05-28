@echo off
@rem UE5 Editor Build
setlocal
pushd "%~dp0"

echo.
echo =========================================
echo Run %~nx0
echo Current Directory: %CD%
echo =========================================
echo.
call ProjectConfig.bat
if %ERRORLEVEL% NEQ 0 goto FAILED

call ..\Setup.bat
if %ERRORLEVEL% NEQ 0 goto FAILED

call ..\GenerateProjectFiles.bat
if %ERRORLEVEL% NEQ 0 goto FAILED


set UPROJECT_NAME=%PROJECT_NAME%.uproject
set PROJECT_EDITOR=%PROJECT_NAME%Editor

echo.
echo [Build GameModule...]
set BUILD_ARGS=Win64 -project="%CLIENT_DIR%\%UPROJECT_NAME%" -progress -NoHotReloadFromIDE -deploy -waitmutex -2022

%UBT_EXE_PATH% %PROJECT_EDITOR% Development %BUILD_ARGS%
if %ERRORLEVEL% NEQ 0 goto FAILED

@rem Done!!!
goto DONE

:FAILED
echo [31m -------- EditorBuild.bat Failed!! -------- [0m
echo ERRORLEVEL is %ERRORLEVEL%
goto END

:DONE
echo [32m-------- EditorBuild.bat Done! -------- [0m
goto END

:END
popd
endlocal
echo.
