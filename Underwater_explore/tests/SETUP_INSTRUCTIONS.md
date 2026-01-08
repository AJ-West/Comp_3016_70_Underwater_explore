# Unit Test Setup Instructions

This guide will help you set up and run the unit tests for the Underwater_explore project.

## Prerequisites

- Visual Studio 2022 (Community or higher)
- Windows 10/11
- Git (for cloning vcpkg)

## Step 1: Install Google Test

### Method A: Using vcpkg (Recommended)

1. **Install vcpkg** (if not already installed):
   ```powershell
   # Navigate to a directory where you want vcpkg (e.g., C:\dev)
   cd C:\dev
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat
   ```

2. **Install Google Test**:
   ```powershell
   .\vcpkg install gtest:x64-windows
   ```

3. **Integrate vcpkg with Visual Studio**:
   ```powershell
   .\vcpkg integrate install
   ```

4. **Set VCPKG_ROOT environment variable** (if not set automatically):
   - Open System Properties > Environment Variables
   - Add new system variable: `VCPKG_ROOT` = `C:\dev\vcpkg` (or your vcpkg path)

### Method B: Using NuGet Package Manager

1. Open Visual Studio
2. Right-click on your solution
3. Select "Manage NuGet Packages for Solution"
4. Search for "googletest" and look for a package with "v143" in the name (for Visual Studio 2022)
   - Example: `Microsoft.googletest.v143.windesktop.msvcstl.static.rt-dyn`
5. Install the package

### Method C: Manual Installation

1. Download Google Test from: https://github.com/google/googletest/releases
2. Extract to a folder (e.g., `C:\Libraries\googletest`)
3. Build it using CMake or include source files directly
4. Update the project file include/library paths

## Step 2: Add Test Project to Solution

1. Open `Underwater_explore.sln` in Visual Studio
2. Right-click on the solution in Solution Explorer
3. Select "Add" > "Existing Project"
4. Navigate to and select `Underwater_explore_Tests.vcxproj`
5. Click "Open"

## Step 3: Configure Project Dependencies

1. Right-click on the solution
2. Select "Project Dependencies"
3. Ensure the test project can access the main project's source files
4. The test project is already configured to include the necessary source files

## Step 4: Update Include Paths (if needed)

If you installed Google Test manually or in a non-standard location:

1. Right-click on `Underwater_explore_Tests` project
2. Select "Properties"
3. Go to "C/C++" > "General" > "Additional Include Directories"
4. Add the path to Google Test headers (e.g., `C:\Libraries\googletest\googletest\include`)

5. Go to "Linker" > "General" > "Additional Library Directories"
6. Add the path to Google Test libraries (e.g., `C:\Libraries\googletest\lib`)

## Step 5: Build the Test Project

1. Set `Underwater_explore_Tests` as the startup project:
   - Right-click on `Underwater_explore_Tests` in Solution Explorer
   - Select "Set as StartUp Project"

2. Build the solution:
   - Press `F7` or go to "Build" > "Build Solution"
   - Ensure the build succeeds without errors

## Step 6: Run the Tests

### Option 1: Run from Visual Studio

1. Press `Ctrl+F5` (Start Without Debugging) or `F5` (Start With Debugging)
2. Tests will run in the console window
3. Results will be displayed in the Output window

### Option 2: Run from Test Explorer

1. Build the solution
2. Go to "Test" > "Test Explorer" (or press `Ctrl+E, T`)
3. All tests should appear in the Test Explorer window
4. Click "Run All" to execute all tests
5. View results in the Test Explorer window

### Option 3: Run from Command Line

1. Build the project
2. Navigate to the output directory:
   ```powershell
   cd Underwater_explore\x64\Debug
   ```
3. Run the test executable:
   ```powershell
   .\Underwater_explore_Tests.exe
   ```

## Expected Output

When tests run successfully, you should see output like:

```
Running main() from gtest_main.cc
[==========] Running 20 tests from 4 test suites.
[----------] Global test environment set-up.
[----------] 5 tests from ProceduralGenerationTest
[ RUN      ] ProceduralGenerationTest.NoiseGenerationInitialization
[       OK ] ProceduralGenerationTest.NoiseGenerationInitialization (2 ms)
[ RUN      ] ProceduralGenerationTest.BiomeGenerationCompletes
[       OK ] ProceduralGenerationTest.BiomeGenerationCompletes (15 ms)
...
[==========] 20 tests from 4 test suites ran. (50 ms total)
[  PASSED  ] 20 tests.
```

## Troubleshooting

### Error: Cannot open include file 'gtest/gtest.h'

**Solution**: Google Test is not found. Check:
- vcpkg integration is installed (`vcpkg integrate install`)
- Include paths in project properties are correct
- Google Test is installed for x64-windows platform

### Error: Unresolved external symbol

**Solution**: Libraries are not linked. Check:
- Library paths in project properties
- Additional Dependencies includes `gtest.lib` and `gtest_main.lib`
- You're building for x64 platform (not x86)

### Error: Model loading fails in tests

**Solution**: Some tests may try to load models. Either:
- Mock the model loading
- Ensure model files exist in the expected paths
- Skip model-dependent tests if running in headless mode

### Tests run but some fail

**Solution**: Check the test output for specific failure messages. Common issues:
- Floating point precision (use `EXPECT_NEAR` instead of `EXPECT_FLOAT_EQ`)
- Random seed differences (tests use fixed seeds for determinism)
- Missing initialization

### vcpkg not found

**Solution**: Set the `VCPKG_ROOT` environment variable:
```powershell
# In PowerShell (temporary)
$env:VCPKG_ROOT = "C:\dev\vcpkg"

# Or set permanently in System Environment Variables
```

## Next Steps

- Add more tests as you develop new features
- Run tests before committing code
- Use test-driven development (TDD) for new features
- Consider adding integration tests for full game loop

## Additional Resources

- Google Test Documentation: https://google.github.io/googletest/
- vcpkg Documentation: https://github.com/Microsoft/vcpkg
- Visual Studio Testing: https://docs.microsoft.com/en-us/visualstudio/test/

