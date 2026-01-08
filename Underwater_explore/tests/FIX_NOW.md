# Quick Fix: "Cannot find gtest/gtest.h"

## Fastest Solution: Use NuGet (No Installation Required!)

This is the easiest way if you just want to get tests running:

1. **Open Visual Studio**
2. **Right-click on your solution** (`Underwater_explore.sln`) in Solution Explorer
3. **Select "Manage NuGet Packages for Solution"**
4. **Click the "Browse" tab**
5. **Search for:** `googletest`
6. **Select:** `Microsoft.googletest.v143.windesktop.msvcstl.static.rt-dyn` (or search for "googletest" and pick the v143/VS2022 version)
7. **Check the box next to `Underwater_explore_Tests` project**
8. **Click "Install"**
9. **Wait for installation to complete**
10. **Rebuild the test project** (Right-click → Rebuild)

That's it! NuGet will automatically configure all the paths.

---

## Alternative: Check Your vcpkg Setup

If you prefer using vcpkg, check these:

### 1. Is VCPKG_ROOT set?

Open PowerShell and run:
```powershell
$env:VCPKG_ROOT
```

If nothing appears, you need to set it:
```powershell
# Temporary (current session only)
$env:VCPKG_ROOT = "C:\vcpkg"  # or wherever you installed vcpkg

# Permanent (recommended)
[System.Environment]::SetEnvironmentVariable("VCPKG_ROOT", "C:\vcpkg", [System.EnvironmentVariableTarget]::User)
```

**Then restart Visual Studio!**

### 2. Is Google Test installed?

Check if this file exists:
```
C:\vcpkg\installed\x64-windows\include\gtest\gtest.h
```

If not, install it:
```powershell
cd C:\vcpkg
.\vcpkg install gtest:x64-windows
```

### 3. Is vcpkg integrated with Visual Studio?

```powershell
cd C:\vcpkg
.\vcpkg integrate install
```

---

## Still Not Working?

1. **Close Visual Studio completely**
2. **Set VCPKG_ROOT** (see above)
3. **Restart Visual Studio**
4. **Clean Solution** (Build → Clean Solution)
5. **Rebuild** (Build → Rebuild Solution)

If it still doesn't work, see `TROUBLESHOOTING.md` for more detailed solutions.

