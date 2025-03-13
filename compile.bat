@echo off
cls
rmdir /s /q "build"
mkdir "build"
cd "build"
cmake ".." "-DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake"
cmake "--build" "."
cd ..