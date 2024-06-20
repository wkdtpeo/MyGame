@echo off
@rem BuildGraph
setlocal
pushd "%~dp0"

echo [Run %~nx0]

call GetProjectConfig.bat
if %ERRORLEVEL% NEQ 0 goto FAILED

echo [Run BuildGraph]
set RUN_UAT_BAT=%ENGINE_DIR%\Build\BatchFiles\RunUAT.bat
if not exist %RUN_UAT_BAT% (
goto FAILED 
)

@REM Engine Build
call %RUN_UAT_BAT% BuildGraph -Script=Engine/Build/InstalledEngineBuild.xml -Target="%TARGET_NAME%" -set:HostPlatformOnly=true
if %ERRORLEVEL% NEQ 0 goto FAILED

@REM ProjecY Editor Build
call %RUN_UAT_BAT% BuildGraph -Script=ProjectY/Build/EditorBuild.xml -Target="ProjectYEditor" -set:UProjectPath=%CLIENT_DIR%\%PROJECT_NAME%.uproject
if %ERRORLEVEL% NEQ 0 goto FAILED

@rem END!!
goto END

:FAILED
echo.
echo ERRORLEVEL is %ERRORLEVEL%
echo ########### %~nx0 Run Error!! #############
echo.
exit /b 1

:END
echo [End %~nx0]
echo.
popd
endlocal