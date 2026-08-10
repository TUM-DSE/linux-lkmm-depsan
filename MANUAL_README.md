# LKMM Dep Checker Manual Setup

Run the dependency analysis step-by-step in a nix shell.

## Setup

```sh
nix develop
export LKMM_OUTDIR=$(pwd)/output/results/$(uname -m)/latest
```

## 1. Configure & Build

```sh
scripts/depsan/go.sh config
scripts/depsan/go.sh run
```

This runs `allmodconfig` with analysis options enabled, then builds the kernel with the custom LLVM passes. Results are written to `$LKMM_OUTDIR`.

## 2. Model Checking

```sh
scripts/depsan/go.sh modelcheck /path/to/linux-kernel.cat
```

Runs Dartagnan on all non-empty analysis results. Logs go to `output/dartagnan-logs/`, CSV to `output/<arch>.csv`.

## 3. Plots

```sh
python3 scripts/depsan/plot.py --results output --arch <arch> --outdir output/plots
```

## Output

```
output/
  results/<arch>/latest/   per-module analysis results
  <arch>.csv               model checker CSV
  dartagnan-logs/          raw dartagnan logs
  plots/                   PDF plots
```
