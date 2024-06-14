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

if "%RUN_SETUP_BAT%"=="true" (
echo [Run Setup.bat]
call ..\Setup.bat
if %ERRORLEVEL% NEQ 0 goto FAILED
echo [End Setup.bat]
)

echo [Run GenerateProjectFiles.bat]
call ..\GenerateProjectFiles.bat
if %ERRORLEVEL% NEQ 0 goto FAILED
echo [End GenerateProjectFiles.bat]

call GetProjectConfig.bat
if %ERRORLEVEL% NEQ 0 goto FAILED

set UPROJECT_NAME=%PROJECT_NAME%.uproject
set PROJECT_EDITOR=%PROJECT_NAME%Editor

echo.
echo [Build Essential EngineModules...]
set BUILD_BAT=%ENGINE_DIR%\Build\BatchFiles\Build.bat

@REM ShaderCompileWorker
set ESSENTIAL_BUILD_ARGS=Win64 Development -waitmutex -NoXge -2022
call %BUILD_BAT% ShaderCompileWorker %ESSENTIAL_BUILD_ARGS%
if %ERRORLEVEL% NEQ 0 goto FAILED

@REM UBT Build
if "%RUN_BULID_TYPE%"=="UBT" (
echo.
echo [UBT Build]
set BUILD_ARGS=Win64 -project="%CLIENT_DIR%\%UPROJECT_NAME%" -progress -NoHotReloadFromIDE -deploy -waitmutex -NoXge -NoUBTMakefiles -2022
@rem -NoXge : 분산 빌드 프로세스 비활성화
@rem -NoUBTMakefiles : 타겟 데이터를 캐싱하여 매우 빠른 반복 빌드 지원여부 (자세한 내용은 Engine\Source\Programs\UnrealBuildTool\Configuration.cs 에 검색하여 참고)
@rem -NoHotReloadFromIDE : True if hot-reload from IDE is allowed

%UBT_EXE_PATH% %PROJECT_EDITOR% Development %BUILD_ARGS%
if %ERRORLEVEL% NEQ 0 goto FAILED
)

@REM BuildGraph Build
if "%RUN_BULID_TYPE%"=="BUILD_GRAPH" (
echo.
echo [BuildGraph Build]
set BUILD_UAT_BAT=%ENGINE_DIR%\Build\BatchFiles\BuildUAT.bat
call BuildGraph.bat
echo.
echo [End BuildGraph]
if %ERRORLEVEL% NEQ 0 goto FAILED
)

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
