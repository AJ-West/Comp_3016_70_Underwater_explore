# Quick Start Guide - Running Unit Tests

## Fastest Way to Get Tests Running

### ⚡ Quickest Solution: Use NuGet (Recommended for First-Time Setup)

1. **Open Visual Studio**
2. **Right-click on solution** → "Manage NuGet Packages for Solution"
3. **Browse tab** → Search: `googletest`
4. **Install:** `Microsoft.googletest.v143.windesktop.msvcstl.static.rt-dyn` (or search for "googletest" and pick the v143 version)
5. **Select `Underwater_explore_Tests` project** → Click Install
6. **Done!** Rebuild and run.

No environment variables, no command line needed!

---

### Alternative: Install Google Test via vcpkg

**Option A: Use the automated script (Easiest)**

Open PowerShell in the `tests` folder and run:
```powershell
.\install_gtest.ps1
```

**Option B: Manual installation**

Open PowerShell and run:

```powershell
# If you don't have vcpkg, install it first:
cd C:\
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

# Set environment variable (permanent)
[System.Environment]::SetEnvironmentVariable("VCPKG_ROOT", "C:\vcpkg", [System.EnvironmentVariableTarget]::User)
$env:VCPKG_ROOT = "C:\vcpkg"

# Integrate with Visual Studio
.\vcpkg integrate install

# Install Google Test
.\vcpkg install gtest:x64-windows
```

**Important:** After setting VCPKG_ROOT, restart Visual Studio!

### Step 2: Add Test Project to Solution (If not already added)

1. Open `Underwater_explore.sln` in Visual Studio
2. Right-click solution → "Add" → "Existing Project"
3. Select `Underwater_explore_Tests.vcxproj`

### Step 3: Build and Run

1. Set `Underwater_explore_Tests` as startup project (right-click → "Set as StartUp Project")
2. Press `F7` to build
3. Press `Ctrl+F5` to run tests

## Alternative: Using NuGet

1. Right-click solution → "Manage NuGet Packages"
2. Search for "googletest"
3. Install "Microsoft.googletest.v143.windesktop.msvcstl.static.rt-dyn" (or the latest googletest package for v143)
4. Build and run as above

## What Tests Are Included?

- **Procedural Generation**: Tests noise generation, biome placement, collectable spawning
- **Player**: Tests collision detection, camera initialization
- **Collectable**: Tests position calculations, size consistency
- **Math Utilities**: Tests vector operations, distance calculations

## Expected Output

```
[==========] Running 20 tests from 4 test suites.
[  PASSED  ] 20 tests.
```

## Troubleshooting

**"Cannot find gtest/gtest.h"**
- **Most common issue!** See `TROUBLESHOOTING.md` for detailed solutions
- Quick fix: Make sure VCPKG_ROOT is set and restart Visual Studio
- Run the installation script: `.\install_gtest.ps1`
- Or use NuGet: Right-click solution → Manage NuGet Packages → Search "googletest"

**"Unresolved external symbol"**
- Ensure you're building for x64 platform
- Check that gtest.lib is in Additional Dependencies

**Tests fail due to model loading**
- Some tests require model files - ensure `art/models/bottle/bottle.obj` exists
- Tests will skip gracefully if models aren't found

For detailed setup instructions, see `SETUP_INSTRUCTIONS.md`

