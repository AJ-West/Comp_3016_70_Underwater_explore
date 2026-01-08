# Troubleshooting: "Cannot find gtest/gtest.h"

This error means Google Test is not installed or the include paths are not configured correctly.

## Solution 1: Install Google Test via vcpkg (Recommended)

### Step 1: Check if vcpkg is installed

Open PowerShell and check:
```powershell
$env:VCPKG_ROOT
```

If nothing is returned, vcpkg is not installed or VCPKG_ROOT is not set.

### Step 2: Install vcpkg (if needed)

```powershell
# Navigate to where you want vcpkg (e.g., C:\dev)
cd C:\dev
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
```

### Step 3: Set VCPKG_ROOT environment variable

**Temporary (for current session):**
```powershell
$env:VCPKG_ROOT = "C:\dev\vcpkg"
```

**Permanent (recommended):**
1. Press `Win + X` and select "System"
2. Click "Advanced system settings"
3. Click "Environment Variables"
4. Under "System variables", click "New"
5. Variable name: `VCPKG_ROOT`
6. Variable value: `C:\dev\vcpkg` (or your vcpkg path)
7. Click OK on all dialogs
8. **Restart Visual Studio** for changes to take effect

### Step 4: Integrate vcpkg with Visual Studio

```powershell
cd C:\dev\vcpkg  # or your vcpkg path
.\vcpkg integrate install
```

You should see: "Applied user-wide integration for this vcpkg instance."

### Step 5: Install Google Test

```powershell
.\vcpkg install gtest:x64-windows
```

This will take a few minutes. You should see:
```
The following packages will be built and installed:
    gtest[core]:x64-windows
```

### Step 6: Verify installation

Check that these directories exist:
- `C:\dev\vcpkg\installed\x64-windows\include\gtest\gtest.h`
- `C:\dev\vcpkg\installed\x64-windows\lib\gtest.lib`

### Step 7: Rebuild in Visual Studio

1. Close Visual Studio
2. Reopen the solution
3. Clean solution (Build > Clean Solution)
4. Rebuild (Build > Rebuild Solution)

## Solution 2: Manual Installation (If vcpkg doesn't work)

### Step 1: Download Google Test

1. Go to: https://github.com/google/googletest/releases
2. Download the latest release (e.g., `googletest-1.14.0.zip`)
3. Extract to a folder (e.g., `C:\Libraries\googletest`)

### Step 2: Build Google Test

You have two options:

**Option A: Use CMake (if you have it)**
```powershell
cd C:\Libraries\googletest
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Debug
cmake --build . --config Release
```

**Option B: Use Pre-built Binaries**
- Download pre-built binaries if available
- Or use the header-only approach (see Solution 3)

### Step 3: Update Project Properties

1. Right-click `Underwater_explore_Tests` project in Visual Studio
2. Select "Properties"
3. Go to "C/C++" > "General" > "Additional Include Directories"
4. Add: `C:\Libraries\googletest\googletest\include`
5. Go to "Linker" > "General" > "Additional Library Directories"
6. Add: `C:\Libraries\googletest\build\lib\Debug` (for Debug)
7. Add: `C:\Libraries\googletest\build\lib\Release` (for Release)
8. Click OK

## Solution 3: Use Header-Only Google Test (Simplest)

If you just want to get tests running quickly, you can use a header-only version.

### Step 1: Download Single Header

1. Create folder: `Underwater_explore\tests\gtest`
2. Download `gtest.h` from: https://raw.githubusercontent.com/google/googletest/main/googletest/include/gtest/gtest.h
3. Save it to: `Underwater_explore\tests\gtest\gtest.h`

### Step 2: Update Test Files

Change the include in all test files from:
```cpp
#include <gtest/gtest.h>
```

To:
```cpp
#include "gtest/gtest.h"
```

### Step 3: Update Project File

The project file already includes `$(ProjectDir)` in the include paths, so it should find the header.

**Note:** This is a simplified approach and may not work for all Google Test features. For full functionality, use Solution 1 or 2.

## Solution 4: Use NuGet Package Manager

### Step 1: Install via NuGet

1. Right-click on the solution in Visual Studio
2. Select "Manage NuGet Packages for Solution"
3. Click "Browse" tab
4. Search for: `googletest`
5. Look for a package with "v143" in the name (for Visual Studio 2022)
   - Example: `Microsoft.googletest.v143.windesktop.msvcstl.static.rt-dyn`
6. Select the package and click "Install"
7. Select the `Underwater_explore_Tests` project
8. Click OK

### Step 2: Verify

The NuGet package should automatically configure include and library paths. Rebuild the project.

## Verification

After following any solution, verify it works:

1. Open any test file (e.g., `test_player.cpp`)
2. Hover over `#include <gtest/gtest.h>`
3. Right-click and select "Go to Definition"
4. If it opens `gtest.h`, the include path is correct!

## Still Having Issues?

1. **Check the actual error message** - it will tell you which path it's looking in
2. **Verify VCPKG_ROOT** - In Visual Studio, go to Project Properties > VC++ Directories and check if `$(VCPKG_ROOT)` resolves correctly
3. **Check Output Window** - Build the project and check the Output window for the actual include paths being used
4. **Restart Visual Studio** - Sometimes environment variable changes require a restart

## Quick Check Script

Run this in PowerShell to check your setup:

```powershell
# Check vcpkg
if ($env:VCPKG_ROOT) {
    Write-Host "VCPKG_ROOT: $env:VCPKG_ROOT" -ForegroundColor Green
    if (Test-Path "$env:VCPKG_ROOT\installed\x64-windows\include\gtest\gtest.h") {
        Write-Host "Google Test found!" -ForegroundColor Green
    } else {
        Write-Host "Google Test NOT found. Run: vcpkg install gtest:x64-windows" -ForegroundColor Red
    }
} else {
    Write-Host "VCPKG_ROOT not set!" -ForegroundColor Red
}
```

