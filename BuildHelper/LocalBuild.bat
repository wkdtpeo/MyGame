@echo off
@rem UE5 Editor Build
setlocal
pushd "%~dp0"

@REM Build Option...
@REM RUN_BULID_TYPE : UBT, BUILD_GRAPH
@REM TARGET_NAME : Editor Win64, Target Win64
set RUN_SETUP_BAT="false"
set RUN_BULID_TYPE=BUILD_GRAPH
set TARGET_NAME=Editor Win64

call EditorBuild.bat