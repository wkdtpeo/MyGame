@echo off
@rem ProjectY Configuration

echo [Run %~nx0]

@rem 프로젝트명
set PROJECT_NAME=ProjectY
echo #PROJECT_NAME : %PROJECT_NAME%

@rem UE5 엔진 경로
set ENGINE_DIR=..\Engine
if not exist %ENGINE_DIR% ( 
    echo ENGINE_DIR ERROR! 
    goto FAILED
) 

pushd %ENGINE_DIR%
set ENGINE_DIR=%cd%
echo #ENGINE_DIR : %ENGINE_DIR%
popd

@rem 프로젝트 경로
set CLIENT_DIR=..\%PROJECT_NAME%
if not exist %CLIENT_DIR% ( 
    echo CLIENT_DIR ERROR! 
    goto FAILED
) 

pushd %CLIENT_DIR%
set CLIENT_DIR=%cd%
echo #CLIENT_DIR : %CLIENT_DIR%
popd

@rem UnrealBuildTool.exe 경로
set UBT_DIR=%ENGINE_DIR%\Binaries\DotNET\UnrealBuildTool\
set UBT_EXE=UnrealBuildTool.exe
set UBT_EXE_PATH=%UBT_DIR%%UBT_EXE%
if not exist %UBT_EXE_PATH% ( 
echo UBT_EXE ERROR!! : %UBT_EXE_PATH%
goto FAILED
)

@rem END!!
goto END

:FAILED
echo.
echo ########### %~nx0 Run Error!! #############
echo.

goto END

:END
echo [End %~nx0]
echo.