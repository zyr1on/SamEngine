@echo off
del bin\OpenGL.exe
cls
REM build klasörü var mı kontrol et
if exist build (
    echo [Info] Build file found ...
    cmake --build build --config Release
) else (
    echo [Info] Build file not found ...
    cmake -S . -B build -G "MinGW Makefiles"
    cmake --build build --config Release --clean-first
)

REM Çalıştırılabilir dosyayı çalıştır
cd bin
OpenGL.exe
cd ..
