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

call GetProjectConfig.bat
if %ERRORLEVEL% NEQ 0 goto FAILED

echo [InstalledEngineBuild...]
set TARGET_NAME=Editor Win64
set RUN_UAT_BAT=%ENGINE_DIR%\Build\BatchFiles\RunUAT.bat
if not exist %RUN_UAT_BAT% (
goto FAILED 
)

call InstalledEngineBuild.bat
echo.
echo [End InstalledEngineBuild]
if %ERRORLEVEL% NEQ 0 goto FAILED

@rem Done!
goto DONE

:FAILED
echo [31m -------- EditorBuild.bat Failed!! -------- [0m
echo ERRORLEVEL is %ERRORLEVEL%
goto END

:DONE
echo [32m-------- EditorBuild.bat Done! -------- [0m

:END
popd
endlocal
echo.