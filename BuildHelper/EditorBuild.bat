@echo off
@rem UE5 Editor Build
setlocal
pushd "%~dp0"

echo.
echo =========================================
echo Run EditorBuild.bat
echo =========================================
echo Run %~nx0
echo Current Directory: %CD%

echo.
echo =========================================
echo Unreal Engine Setup...
echo =========================================
call ..\Setup.bat
if %ERRORLEVEL% NEQ 0 goto FAILED

@rem Done!
goto DONE

:FAILED
echo -------- EditorBuild.bat Failed!! -------- 
echo ERRORLEVEL is %ERRORLEVEL%
goto DONE

:DONE
echo -------- EditorBuild.bat Done! -------- 
popd
endlocal
echo.
