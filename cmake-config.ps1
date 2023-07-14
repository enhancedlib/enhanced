# TODO: More options and features

if (-not (Get-Command "cmake.exe" -ErrorAction SilentlyContinue)) {
    Write-Error "cmake not found"
    exit 1
}

cmake --version | Select-Object -First 1

if (-not (Get-Command "ninja.exe" -ErrorAction SilentlyContinue)) {
    Write-Error "ninja not found"
    exit 1
}

$BUILD_DIR = $args[0]
if (-not $BUILD_DIR) {
    $BUILD_DIR = "build"
}
$INSTALL_DIR = $args[1]
if (-not $INSTALL_DIR) {
    $INSTALL_DIR = "release"
}

if (Test-Path $BUILD_DIR) {
    $CMAKE_CONFIG_CMD_LINE = "cmake -DCMAKE_INSTALL_PREFIX=`"$INSTALL_DIR`" -G Ninja -B `"$BUILD_DIR`" ."
} else {
    $TOOLCHAINS = @{}

    if ($CLANG_COMMAND = (Get-Command "clang.exe" -ErrorAction SilentlyContinue).Source) {
        $TOOLCHAINS["clang"] = "`"$CLANG_COMMAND`";`"$((Get-Command "clang++.exe" -ErrorAction SilentlyContinue).Source)`""
        if (-not $FALLBACK_TOOLCHAIN) {
            $FALLBACK_TOOLCHAIN = "clang"
        }
    }

    if ($GCC_COMMAND = (Get-Command "gcc.exe" -ErrorAction SilentlyContinue).Source) {
        if ($GCC_CPP_COMMAND = (Get-Command "g++.exe" -ErrorAction SilentlyContinue).Source) {
            $TOOLCHAINS["gcc"] = "`"$GCC_COMMAND`";`"$GCC_CPP_COMMAND`""
            if (-not $FALLBACK_TOOLCHAIN) {
                $FALLBACK_TOOLCHAIN = "gcc"
            }
        }
    }

    if ($MSVC_COMMAND = (Get-Command "cl.exe" -ErrorAction SilentlyContinue).Source) {
        $TOOLCHAINS["msvc"] = "`"$MSVC_COMMAND`""
        if (-not $FALLBACK_TOOLCHAIN) {
            $FALLBACK_TOOLCHAIN = "msvc"
        }
    }

    if ($TOOLCHAINS.Count -eq 0) {
        Write-Error "No toolchain found."
        exit 1
    } else {
        if ($TOOLCHAINS.Count -eq 1) {
            Write-Host "Toolchain: $($TOOLCHAINS.Keys) ($($TOOLCHAINS.Values))"
            $CHOSEN_TOOLCHAIN = $($TOOLCHAINS.Keys)
        } else {
            Write-Host "Found multiple toolchains:"
            foreach ($TOOLCHAIN in $TOOLCHAINS.Keys) {
                Write-Host " - ${TOOLCHAIN}: $($TOOLCHAINS[$TOOLCHAIN])"
            }
            do {
                $CHOSEN_TOOLCHAIN = Read-Host "Choose a toolchain (default: ${FALLBACK_TOOLCHAIN})"
                if (-not $CHOSEN_TOOLCHAIN) {
                    $CHOSEN_TOOLCHAIN = $FALLBACK_TOOLCHAIN
                    break
                } else {
                    if (-not ($TOOLCHAINS.ContainsKey($CHOSEN_TOOLCHAIN))) {
                        Write-Warning "Invalid toolchain."
                    } else {
                        break
                    }
                }
            } while ($true)
        }
    }

    if ("$CHOSEN_TOOLCHAIN" -ne "msvc") {
        $CMAKE_CONFIG_CMD_LINE = "cmake -DCMAKE_C_COMPILER:FILEPATH=$(($TOOLCHAINS[$CHOSEN_TOOLCHAIN].Split(";")[0])) -DCMAKE_CXX_COMPILER:FILEPATH=" +
        "$(($TOOLCHAINS[$CHOSEN_TOOLCHAIN].Split(";")[1])) -DCMAKE_INSTALL_PREFIX=`"$INSTALL_DIR`" -G Ninja -B `"$BUILD_DIR`" ."
    } else {
        $CMAKE_CONFIG_CMD_LINE = "cmake -DCMAKE_C_COMPILER:FILEPATH=$($TOOLCHAINS["msvc"]) -DCMAKE_CXX_COMPILER:FILEPATH=$($TOOLCHAINS["msvc"]) " +
        "-DCMAKE_INSTALL_PREFIX=`"$INSTALL_DIR`" -G Ninja -B `"$BUILD_DIR`" ."
    }
}

Write-Host "$ $CMAKE_CONFIG_CMD_LINE"

Invoke-Expression "$CMAKE_CONFIG_CMD_LINE"
