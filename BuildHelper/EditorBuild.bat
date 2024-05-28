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

echo [Run Setup.bat]
call ..\Setup.bat
if %ERRORLEVEL% NEQ 0 goto FAILED
echo [End Setup.bat]

echo [Run GenerateProjectFiles.bat]
call ..\GenerateProjectFiles.bat
if %ERRORLEVEL% NEQ 0 goto FAILED
echo [End GenerateProjectFiles.bat]

call ProjectConfig.bat
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
echo -------- EditorBuild.bat Failed!! --------
echo ERRORLEVEL is %ERRORLEVEL%
goto END

:DONE
echo -------- EditorBuild.bat Done! --------
goto END

:END
echo [End EditorBuild.bat]
popd
endlocal
echo.
