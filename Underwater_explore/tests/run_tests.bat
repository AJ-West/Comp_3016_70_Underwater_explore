@echo off
REM Batch script to build and run unit tests
REM Make sure you've built the test project first

echo Building test project...
cd ..
msbuild Underwater_explore_Tests.vcxproj /p:Configuration=Debug /p:Platform=x64 /t:Build

if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo Running tests...
echo.

cd x64\Debug
if exist Underwater_explore_Tests.exe (
    Underwater_explore_Tests.exe
) else (
    echo Test executable not found! Make sure the project built successfully.
    pause
    exit /b 1
)

pause

