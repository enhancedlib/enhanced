#!/usr/bin/bash

# TODO: More options and features

which cmake > /dev/null

echo `cmake --version | head -n 1`

BUILD_DIR=${1:-build}
INSTALL_DIR=${2:-release}

which ninja > /dev/null

declare -A TOOLCHAINS

CLANG_COMMANDS=`find /usr/bin -regex ".*/clang-[0-9]+"`
for CLANG_COMMAND in $CLANG_COMMANDS; do
    NAME=`basename $CLANG_COMMAND`
    CLANG_CPP_COMMAND=/usr/bin/clang++-`echo $NAME | cut -d "-" -f 2`
    TOOLCHAINS[$NAME]="'$CLANG_COMMAND';'$CLANG_CPP_COMMAND'"
    if [ -z "$FALLBACK_TOOLCHAIN" ]; then
        FALLBACK_TOOLCHAIN=$NAME
    fi
done

GCC_COMMANDS=`find /usr/bin -regex ".*/gcc-[0-9]+"`
for GCC_COMMAND in $GCC_COMMANDS; do
    NAME=`basename $GCC_COMMAND`
    GCC_CPP_COMMAND=/usr/bin/g++-`echo $NAME | cut -d "-" -f 2`
    which $GCC_CPP_COMMAND > /dev/null
    if [ $? -eq 0 ]; then
        TOOLCHAINS[$NAME]="'$GCC_COMMAND';'$GCC_CPP_COMMAND'"
        if [ -z "$FALLBACK_TOOLCHAIN" ]; then
            FALLBACK_TOOLCHAIN=$NAME
        fi
    fi
done

if [ ${#TOOLCHAINS[@]} -eq 0 ]; then
    echo "No toolchain found."
    exit 1
else
    if [ ${#TOOLCHAINS[@]} -eq 1 ]; then
        echo "Toolchain: ${!TOOLCHAINS[@]} (${TOOLCHAINS[@]})"
        CHOSEN_TOOLCHAIN=${!TOOLCHAINS[@]}
    else
        echo "Found multiple toolchains:"
        for TOOLCHAIN in "${!TOOLCHAINS[@]}"; do
            echo " - $TOOLCHAIN: ${TOOLCHAINS[$TOOLCHAIN]}"
        done
        read -p "Choose a toolchain (default: ${FALLBACK_TOOLCHAIN}): " CHOSEN_TOOLCHAIN
        if [ -z "${CHOSEN_TOOLCHAIN}" ]; then
            CHOSEN_TOOLCHAIN=$FALLBACK_TOOLCHAIN
        else
            if [ -z "${TOOLCHAINS[$CHOSEN_TOOLCHAIN]}" ]; then
                echo "Invalid toolchain."
                exit 1
            fi
        fi
    fi
fi

CMAKE_CONFIG_CMD_LINE="cmake -DCMAKE_C_COMPILER=`echo ${TOOLCHAINS[$CHOSEN_TOOLCHAIN]} | cut -d ";" -f 1`
-DCMAKE_CXX_COMPILER=`echo ${TOOLCHAINS[$CHOSEN_TOOLCHAIN]} | cut -d ";" -f 2` -DCMAKE_INSTALL_PREFIX='$INSTALL_DIR' -G Ninja -B $BUILD_DIR ."

echo "$ $CMAKE_CONFIG_CMD_LINE"

$CMAKE_CONFIG_CMD_LINE
