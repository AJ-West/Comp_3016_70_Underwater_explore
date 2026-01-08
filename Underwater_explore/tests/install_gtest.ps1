# PowerShell script to install Google Test via vcpkg
# Run this script in PowerShell (as Administrator if needed)

Write-Host "Google Test Installation Script" -ForegroundColor Cyan
Write-Host "================================" -ForegroundColor Cyan
Write-Host ""

# Check if vcpkg exists
$vcpkgPath = $env:VCPKG_ROOT
if (-not $vcpkgPath) {
    Write-Host "VCPKG_ROOT environment variable not set." -ForegroundColor Yellow
    Write-Host ""
    Write-Host "Please choose an option:" -ForegroundColor Yellow
    Write-Host "1. Install vcpkg to C:\dev\vcpkg (recommended)"
    Write-Host "2. Enter custom vcpkg path"
    Write-Host "3. Exit"
    Write-Host ""
    $choice = Read-Host "Enter choice (1-3)"
    
    if ($choice -eq "1") {
        $vcpkgPath = "C:\dev\vcpkg"
        Write-Host "Installing vcpkg to $vcpkgPath..." -ForegroundColor Yellow
        
        # Check if directory exists
        if (-not (Test-Path $vcpkgPath)) {
            Write-Host "Cloning vcpkg repository..." -ForegroundColor Yellow
            $parentDir = Split-Path $vcpkgPath -Parent
            if (-not (Test-Path $parentDir)) {
                New-Item -ItemType Directory -Path $parentDir -Force | Out-Null
            }
            Set-Location $parentDir
            git clone https://github.com/Microsoft/vcpkg.git
        }
        
        # Bootstrap vcpkg
        if (Test-Path "$vcpkgPath\vcpkg.exe") {
            Write-Host "vcpkg already bootstrapped." -ForegroundColor Green
        } else {
            Write-Host "Bootstrapping vcpkg..." -ForegroundColor Yellow
            Set-Location $vcpkgPath
            .\bootstrap-vcpkg.bat
        }
        
        # Set environment variable
        Write-Host "Setting VCPKG_ROOT environment variable..." -ForegroundColor Yellow
        [System.Environment]::SetEnvironmentVariable("VCPKG_ROOT", $vcpkgPath, [System.EnvironmentVariableTarget]::User)
        $env:VCPKG_ROOT = $vcpkgPath
        Write-Host "VCPKG_ROOT set to: $vcpkgPath" -ForegroundColor Green
        Write-Host "Note: You may need to restart Visual Studio for this to take effect." -ForegroundColor Yellow
        
    } elseif ($choice -eq "2") {
        $vcpkgPath = Read-Host "Enter vcpkg path"
        if (-not (Test-Path $vcpkgPath)) {
            Write-Host "Path does not exist: $vcpkgPath" -ForegroundColor Red
            exit 1
        }
        [System.Environment]::SetEnvironmentVariable("VCPKG_ROOT", $vcpkgPath, [System.EnvironmentVariableTarget]::User)
        $env:VCPKG_ROOT = $vcpkgPath
    } else {
        Write-Host "Exiting..." -ForegroundColor Yellow
        exit 0
    }
}

# Verify vcpkg exists
if (-not (Test-Path "$vcpkgPath\vcpkg.exe")) {
    Write-Host "vcpkg.exe not found at: $vcpkgPath" -ForegroundColor Red
    Write-Host "Please ensure vcpkg is properly installed." -ForegroundColor Red
    exit 1
}

Write-Host "vcpkg found at: $vcpkgPath" -ForegroundColor Green
Write-Host ""

# Integrate vcpkg with Visual Studio
Write-Host "Integrating vcpkg with Visual Studio..." -ForegroundColor Yellow
Set-Location $vcpkgPath
.\vcpkg integrate install
Write-Host ""

# Install Google Test
Write-Host "Installing Google Test (this may take a few minutes)..." -ForegroundColor Yellow
.\vcpkg install gtest:x64-windows

if ($LASTEXITCODE -eq 0) {
    Write-Host ""
    Write-Host "========================================" -ForegroundColor Green
    Write-Host "Google Test installed successfully!" -ForegroundColor Green
    Write-Host "========================================" -ForegroundColor Green
    Write-Host ""
    Write-Host "Next steps:" -ForegroundColor Cyan
    Write-Host "1. Restart Visual Studio (if VCPKG_ROOT was just set)" -ForegroundColor White
    Write-Host "2. Rebuild the test project" -ForegroundColor White
    Write-Host "3. Run the tests!" -ForegroundColor White
} else {
    Write-Host ""
    Write-Host "Installation failed. Please check the error messages above." -ForegroundColor Red
    exit 1
}

