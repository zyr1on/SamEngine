@echo off
cls
setlocal

set BUILD_DIR=build
set CONFIG=Release
set EXE=bin\OpenGL.exe

REM detect cores
if defined NUMBER_OF_PROCESSORS (
  set JOBS=%NUMBER_OF_PROCESSORS%
) else (
  set JOBS=4
)

REM prefer Ninja
where ninja >nul 2>&1
if errorlevel 1 (
  echo [Info] ninja not found, using MinGW Makefiles
  set GENERATOR=MinGW Makefiles
) else (
  set GENERATOR=Ninja
)

REM configure if needed
if not exist %BUILD_DIR% (
  echo [Info] Configuring with %GENERATOR%...
  cmake -S . -B %BUILD_DIR% -G "%GENERATOR%"
  if errorlevel 1 (
    echo [Error] CMake configure failed.
    exit /b 1
  )
) else (
  echo [Info] Build dir exists, skipping configure.
)

REM build with parallelism
echo [Info] Building with %JOBS% jobs...
cmake --build %BUILD_DIR% --config %CONFIG% --parallel %JOBS%
if errorlevel 1 (
  echo [Error] Build failed.
  exit /b 1
)

REM run if exists
if exist %EXE% (
  echo [Info] Running %EXE%...
  pushd bin
  echo.
  echo ------------------------------------------
  echo.
  OpenGL.exe
  popd
) else (
  echo [Warning] Executable not found: %EXE%
)
endlocal

