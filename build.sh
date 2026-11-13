#!/bin/bash
# based on the instructions from edk2-platform
set -e
. build_common.sh
# not actually GCC5; it's GCC7 on Ubuntu 18.04.
GCC5_AARCH32_PREFIX=arm-none-eabi- build -j$(nproc) -s -n 0 -a AARCH32 -t GCC5 -p H3Pkg/H3Pkg.dsc
cp workspace/Build/H3Pkg/DEBUG_GCC5/FV/H3PKG_UEFI.fd workspace/UEFI
