# LKMM Dep Checker Docker Image

Run the full dependency checker pipeline (kernel build, static analysis, model checking, plots) in a self-contained container.

## Usage

```sh
docker run --rm \
  --cpuset-cpus=0-31 \
  --tmpfs /build:rw,exec,size=200g \
  -e OWNER_UID=$(id -u) -e OWNER_GID=$(id -g) \
  -v $(pwd)/output:/output \
  lkmm-depchecker-<arch>:latest
```

- `--cpuset-cpus`: cores to use (kernel build is highly parallel)
- `--tmpfs /build:...`: required; kernel build + results need ~50GB
- `OWNER_UID`/`OWNER_GID`: output files are chowned to this user
- `-v ...:/output`: bind mount for results

## Output

```
output/
  results/<arch>/latest/   per-module analysis results (chain IR snipets, stats)
  <arch>.csv               model checker results
  dartagnan-logs/          raw dartagnan output per function
  plots/                   PDF plots
```
