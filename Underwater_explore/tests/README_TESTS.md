# Unit Tests for Underwater_explore

This directory contains unit tests for the Underwater_explore project using Google Test framework.

## Test Coverage

The test suite covers:

1. **Procedural Generation Tests** (`test_procedural_generation.cpp`)
   - Noise generation initialization
   - Biome generation
   - Collectable generation and positioning
   - Lava generation at correct depths
   - Procedural variety with different seeds

2. **Player Tests** (`test_player.cpp`)
   - Player initialization
   - Camera front setter
   - Collision detection (various scenarios)
   - Edge cases for collision detection

3. **Collectable Tests** (`test_collectable.cpp`)
   - Collectable initialization
   - Center point calculations
   - Size consistency
   - Coordinate handling (positive and negative)

4. **Math Utilities Tests** (`test_math_utilities.cpp`)
   - Vector operations (normalization, cross product)
   - Distance calculations
   - Map size constants validation
   - Vector arithmetic operations

## Setting Up Google Test

### Option 1: Using vcpkg (Recommended for Visual Studio)

1. Install vcpkg if you haven't already:
   ```powershell
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat
   ```

2. Install Google Test:
   ```powershell
   .\vcpkg install gtest:x64-windows
   ```

3. Integrate vcpkg with Visual Studio:
   ```powershell
   .\vcpkg integrate install
   ```

### Option 2: Manual Installation

1. Download Google Test from: https://github.com/google/googletest
2. Build it using CMake or include the source files directly
3. Add the include and library paths to your project

### Option 3: Using NuGet (Visual Studio)

1. Right-click on your solution in Visual Studio
2. Select "Manage NuGet Packages for Solution"
3. Search for "googletest" and look for a package with "v143" in the name (for Visual Studio 2022)
   - Example: `Microsoft.googletest.v143.windesktop.msvcstl.static.rt-dyn`
4. Install the package

## Building the Tests

### Using Visual Studio

1. Open the solution file `Underwater_explore.sln`
2. Add the test project (see `Underwater_explore_Tests.vcxproj`)
3. Set the test project as the startup project
4. Build the solution (F7 or Build > Build Solution)
5. Run the tests (Ctrl+F5 or Debug > Start Without Debugging)

### Using Command Line (MSBuild)

```powershell
cd Underwater_explore
msbuild Underwater_explore_Tests.vcxproj /p:Configuration=Debug /p:Platform=x64
```

## Running the Tests

### In Visual Studio

1. Build the test project
2. Right-click on the test project and select "Set as StartUp Project"
3. Press Ctrl+F5 to run without debugging, or F5 to run with debugging
4. Tests will run and results will be displayed in the Output window

### Using Test Explorer

1. Build the solution
2. Open Test Explorer (Test > Test Explorer)
3. All tests should appear in the Test Explorer window
4. Click "Run All" to execute all tests

### From Command Line

After building, navigate to the output directory and run:

```powershell
cd x64\Debug
.\Underwater_explore_Tests.exe
```

## Test Output

Tests will output results in the following format:
- `[PASSED]` - Test passed successfully
- `[FAILED]` - Test failed (with error details)

Example output:
```
[==========] Running 20 tests from 4 test suites.
[----------] Global test environment set-up.
[----------] 5 tests from ProceduralGenerationTest
[ RUN      ] ProceduralGenerationTest.NoiseGenerationInitialization
[       OK ] ProceduralGenerationTest.NoiseGenerationInitialization (5 ms)
...
[==========] 20 tests from 4 test suites ran. (50 ms total)
[  PASSED  ] 20 tests.
```

## Adding New Tests

To add new tests:

1. Create a new test file in the `tests/` directory (e.g., `test_new_feature.cpp`)
2. Include the necessary headers and Google Test
3. Write test cases using the `TEST` or `TEST_F` macros
4. Rebuild the test project
5. Run the tests to verify

Example test structure:
```cpp
#include <gtest/gtest.h>
#include "../your_header.h"

TEST(YourTestSuite, YourTestName) {
    // Arrange
    // Act
    // Assert
    EXPECT_EQ(expected, actual);
}
```

## Notes

- Some tests may require OpenGL context for full functionality, but most logic tests can run without it
- Tests that require OpenGL (like rendering) are not included as they need a graphics context
- The collision detection tests use mock objects and don't require the full game loop
- Procedural generation tests use fixed seeds for deterministic results

## Troubleshooting

### Linker Errors

If you get linker errors:
1. Ensure Google Test libraries are properly linked in project settings
2. Check that library paths are correct
3. Verify you're building for the correct platform (x64)

### Missing Headers

If headers are not found:
1. Check include paths in project settings
2. Ensure all source files are added to the project
3. Verify relative paths in `#include` statements

### Tests Not Running

If tests don't appear:
1. Rebuild the solution
2. Check that test files are included in the project
3. Verify `test_main.cpp` is set as the entry point

