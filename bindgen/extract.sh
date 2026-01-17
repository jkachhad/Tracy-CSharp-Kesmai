#!/bin/bash
DIRECTORY="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

function get_host_operating_system() {
    local UNAME_STRING="$(uname -a)"
    case "${UNAME_STRING}" in
        *Microsoft*)    local HOST_OS="windows";;
        *microsoft*)    local HOST_OS="windows";;
        Linux*)         local HOST_OS="linux";;
        Darwin*)        local HOST_OS="macos";;
        CYGWIN*)        local HOST_OS="linux";;
        MINGW*)         local HOST_OS="windows";;
        *Msys)          local HOST_OS="windows";;
        *)              local HOST_OS="UNKNOWN:${UNAME_STRING}"
    esac
    echo "$HOST_OS"
    return 0
}

OS="$(get_host_operating_system)"

if [[ "$OS" == "windows" ]]; then
    C2FFI_CONFIG_FILE_PATH="$DIRECTORY/config-extract-windows.json"
elif [[ "$OS" == "macos" ]]; then
    C2FFI_CONFIG_FILE_PATH="$DIRECTORY/config-extract-macos.json"
elif [[ "$OS" == "linux" ]]; then
    C2FFI_CONFIG_FILE_PATH="$DIRECTORY/config-extract-linux.json"
else
    echo "Error: Unknown operating system '$OS'" >&2
    exit 1
fi

if ! [[ -x "$(command -v c2ffi)" ]]; then
  echo "Error: 'c2ffi' is not installed. Please visit https://github.com/bottlenoselabs/c2ffi for instructions to install the c2ffi tool." >&2
  exit 1
fi

# Dump the preprocessed translation unit and search for real extern functions.
clang -E -P -dD \
  -I../ext/Tracy \
  ../src/c/production/Tracy/_Tracy.h \
  > /tmp/tracy_pp.h

echo "=== extern prototypes that look like tracy ==="
grep -nE "extern .*___tracy_" /tmp/tracy_pp.h | head -n 50 || true

echo "=== tracy macros (these won't become functions for c2ffi) ==="
grep -nE "^#define Tracy" /tmp/tracy_pp.h | head -n 50 || true

c2ffi extract --config "$C2FFI_CONFIG_FILE_PATH"
