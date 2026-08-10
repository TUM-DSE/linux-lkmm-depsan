#!/usr/bin/env bash
set -e

# The kernel source is in the Nix store (read-only).
# Copy to a writable location for the build.
KERNEL_STORE="$(dirname "$(dirname "$(readlink -f "$0")")")"
BUILD_DIR="/build/linux"

echo "=== DepSan Pipeline ==="

if [ ! -d "$BUILD_DIR/scripts" ]; then
  echo "--- Copying kernel sources to $BUILD_DIR ---"
  mkdir -p "$BUILD_DIR"
  cp -r "$KERNEL_STORE"/. "$BUILD_DIR"/
  chmod -R u+w "$BUILD_DIR"
fi

SCRIPT_DIR="$BUILD_DIR/scripts/depsan"
export LKMM_OUTDIR="${LKMM_OUTDIR:-/output/results}"
echo "Results will be written to: $LKMM_OUTDIR"

# Step 1: Configure kernel
echo "--- Configuring kernel ---"
"$SCRIPT_DIR/go.sh" config

# Step 2: Build kernel with DepSan analysis + generate CSVs
echo "--- Building kernel ---"
"$SCRIPT_DIR/go.sh" run

# Step 3: Generate plots (if model checker data is available)
if [ -d "/input" ] && ls /input/*.csv >/dev/null 2>&1; then
  echo "--- Generating plots ---"
  python3 "$SCRIPT_DIR/plot.py" --results /input --outdir /output/plots
else
  echo "--- Skipping plots (no model checker data at /input) ---"
fi

echo "=== Done ==="
