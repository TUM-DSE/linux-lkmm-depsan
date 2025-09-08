#! /bin/sh

set -e

SCRIPT_DIR=$(dirname "$0")
BASE_DIR=$(realpath "$SCRIPT_DIR/../..")

mkConfig() {
  pushd "$BASE_DIR"
  make randconfig HOSTCC=gcc CC=clang ARCH=x86_64
  ./scripts/config --enable CONFIG_DEBUG_INFO
  ./scripts/config --enable CONFIG_DEBUG_INFO_DWARF_TOOLCHAIN_DEFAULT
  ./scripts/config --disable CONFIG_DEBUG_INFO_REDUCED
  ./scripts/config --enable DEBUG_INFO_COMPRESSED_NONE
  ./scripts/config --disable DEBUG_INFO_COMPRESSED_ZLIB
  ./scripts/config --disable CONFIG_DEBUG_INFO_SPLIT
  ./scripts/config --enable DEBUG_KERNEL
  ./scripts/config --enable DEPSAN
  ./scripts/config --disable UBSAN
  ./scripts/config --disable KASAN
  popd
}

doBuild() {
  pushd "$BASE_DIR"
  echo "Result here: $LKMM_OUTDIR"
  make HOSTCC=gcc CC=clang -j$(nproc)
  popd
}

debugBuild() {
  pushd "$BASE_DIR"
  echo "Result here: $LKMM_OUTDIR"
  NIX_DEBUG=1 make HOSTCC=gcc CC=clang -j1
  popd
}

setupResult() {
  datetime=$(date +%Y-%m-%d_%H-%M)
  res_dir="$SCRIPT_DIR/results/$datetime"

  mkdir -p "$res_dir"
  ln -s -f -n "./$datetime" "$SCRIPT_DIR/results/latest"

  cp $BASE_DIR/.config "$res_dir/config"
  export LKMM_OUTDIR="$res_dir"
}

if [ -z "$1" ]; then
  echo "Usage: $0 <config|run>"
  exit 1
fi

if [ "$1" = "config" ]; then
  mkConfig
elif [ "$1" = "run" ]; then
  setupResult
  doBuild
elif [ "$1" = "debug" ]; then
  setupResult
  debugBuild
else
  echo "Unknown command: $1"
  exit 1
fi
