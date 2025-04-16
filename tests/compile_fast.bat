@echo off
cls
cd "build"
REM cmake ".." "-DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake"
cmake "--build" "."
cd ..