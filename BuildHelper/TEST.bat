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

echo %PROJECT_NAME%
echo %CLIENT_DIR%
echo %UBT_EXE_PATH%

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