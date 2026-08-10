#! /bin/sh

set -e

SCRIPT_DIR=$(dirname "$0")
BASE_DIR=$(realpath "$SCRIPT_DIR/../..")

ARCH=$(uname -m)

if [ $ARCH = "aarch64" ]; then
  KARCH="arm64"
elif [ $ARCH = "x86_64" ]; then
  KARCH=$ARCH
else
  echo "Probably unsupported ARCH; Good luck."
  KARCH=$ARCH
fi

mkConfig() {
  pushd "$BASE_DIR"
  make allmodconfig HOSTCC=gcc CC=clang ARCH=$KARCH
  ./scripts/config --enable CONFIG_DEBUG_INFO
  ./scripts/config --enable CONFIG_DEBUG_INFO_DWARF_TOOLCHAIN_DEFAULT
  ./scripts/config --disable CONFIG_DEBUG_INFO_REDUCED
  ./scripts/config --enable DEBUG_INFO_COMPRESSED_NONE
  ./scripts/config --disable DEBUG_INFO_COMPRESSED_ZLIB
  ./scripts/config --disable CONFIG_DEBUG_INFO_SPLIT
  ./scripts/config --disable DEBUG_KERNEL
  ./scripts/config --enable DEPSAN
  ./scripts/config --disable UBSAN
  ./scripts/config --disable KASAN
  ./scripts/config --disable KCSAN
  ./scripts/config --disable KCOV
  ./scripts/config --disable KSTACK_ERASE
  ./scripts/config --enable MODULES
  ./scripts/config --disable WERROR

  ./scripts/config --disable SCSI_UFSHCD # BUG_ON arm64
  ./scripts/config --disable ICE # BUG_ON arm64
  ./scripts/config --disable PACKING_KUNIT_TEST # BUG_ON arm64
  ./scripts/config --disable BPF_ARCH_SPINLOCK # BUG_ON arm64
  ./scripts/config --disable QUEUED_SPINLOCKS # BUG_ON arm64

  ./scripts/config --disable X86_KERNEL_IBT # We disabled Exports so ibt would bug

  ./scripts/config --disable QUICC_ENGINE # Timeout
  ./scripts/config --disable FRAMEBUFFER_CONSOLE # Timeout
  ./scripts/config --disable FRAMEBUFFER_CONSOLE_ROTATION # Timeout
  ./scripts/config --disable DRM_I915 # Timeout
  ./scripts/config --disable MT7996E # Error: Uninitialized ptr
  ./scripts/config --disable VIDEO_SAMSUNG_S5P_MFC # Error: Uninitialized ptr
  ./scripts/config --disable DRM_MSM_DPU # Error: Uninitialized ptr

  ./scripts/config --disable LOCKDEP # BlockAddr
  ./scripts/config --disable PROVE_LOCKING
  ./scripts/config --disable TRACE_LOCKING
  ./scripts/config --disable DEBUG_LOCK_ALLOC
  ./scripts/config --disable LOCK_STAT
  #./scripts/config --disable TRACEPOINTS
  #./scripts/config --disable FTRACE
  #./scripts/config --disable TRACING
  #./scripts/config --disable HIST_TRIGGERS # Tracing
  #./scripts/config --disable PREEMPTIRQ_TRACEPOINTS # Tracing
  #./scripts/config --disable GENERIC_TRACER # Tracing
  #./scripts/config --disable ENABLE_DEFAULT_TRACERS # Tracing
  #./scripts/config --disable FPROBE_EVENTS # Tracing
#  ./scripts/config -d TRACING \
#     -d BLK_DEV_IO_TRACE \
#     -d DEBUG_NET_SMALL_RTNL \
#     -d DRM_I915_TRACE_GEM \
#     -d DRM_I915_TRACE_GTT \
#     -d ENABLE_DEFAULT_TRACERS \
#     -d FPROBE_EVENTS \
#     -d FTRACE_SYSCALLS \
#     -d FUNCTION_TRACER \
#     -d GENERIC_TRACER \
#     -d HIST_TRIGGERS \
#     -d HWLAT_TRACER \
#     -d IRQSOFF_TRACER \
#     -d KPROBE_EVENTS \
#     -d MMIOTRACE \
#     -d OSNOISE_TRACER \
#     -d PREEMPTIRQ_TRACEPOINTS \
#     -d PREEMPT_TRACER \
#     -d PROFILE_ALL_BRANCHES \
#     -d PROFILE_ANNOTATED_BRANCHES \
#     -d PROVE_LOCKING \
#     -d RV \
#     -d RV_MON_SLEEP \
#     -d SCHED_TRACER \
#     -d STACK_TRACER \
#     -d SYNTH_EVENTS \
#     -d TIMERLAT_TRACER \
#     -d TRACE_BRANCH_PROFILING \
#     -d UPROBE_EVENTS \
#     -d USER_EVENTS
#
  ./scripts/config --disable PROFILE_ALL_BRANCHES
  ./scripts/config --disable PROFILE_ANNOTATED_BRANCHES
  ./scripts/config --disable STACK_TRACER



  make olddefconfig HOSTCC=gcc CC=clang
  make modules_prepare HOSTCC=gcc CC=clang
  popd
}

mkDebugConfig() {
  pushd "$BASE_DIR"
  make randconfig HOSTCC=gcc CC=$PWD/clang-wrapper ARCH=$KARCH
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
  ./scripts/config --disable KCSAN
  ./scripts/config --disable KCOV
  ./scripts/config --disable KSTACK_ERASE
  popd
}

doBuild() {
  pushd "$BASE_DIR"
  echo "Result here: $LKMM_OUTDIR"
  make HOSTCC=gcc CC=$PWD/clang-wrapper -k -j$(nproc) || true
  popd
  pushd "$LKMM_OUTDIR"
  find -iname matched_chains.txt -size 0 | xargs dirname > EMPTY
  find -iname matched_chains.txt -size +0 | xargs dirname > NON-EMPTY
  popd
  python3 "$SCRIPT_DIR/toCSV.py"
}

debugBuild() {
  pushd "$BASE_DIR"
  echo "Result here: $LKMM_OUTDIR"
  make HOSTCC=gcc CC=$PWD/clang-wrapper -j1
  popd
}

kernel_litmus() {
  pushd "$BASE_DIR"
  echo "Result here: $LKMM_OUTDIR"
  make -C . M=scripts/depsan/examples/kernel-litmus/ MO=scripts/depsan/examples/kernel-litmus/ HOSTCC=gcc CC=clang LKMM_OUTDIR=$BASE_DIR/scripts/depsan/examples/kernel-litmus/results
  popd
}

setupResult() {
  if [ -n "$LKMM_OUTDIR" ]; then
    mkdir -p "$LKMM_OUTDIR"
    cp "$BASE_DIR/.config" "$LKMM_OUTDIR/config"
    return
  fi

  arch=$KARCH
  datetime=$(date +%Y-%m-%d_%H-%M)
  user=$(whoami)
  share_dir="/share/$user"

  if [ -d "$share_dir" ]; then
    base_res="$share_dir/results"
  else
    base_res="$BASE_DIR/results"
  fi

  res_dir="$base_res/$arch/$datetime"
  mkdir -p "$res_dir"
  ln -s -f -n "./$datetime" "$base_res/$arch/latest"

  cp "$BASE_DIR/.config" "$res_dir/config"
  export LKMM_OUTDIR="$res_dir"
}

doModelCheck() {
  if [ -z "$LKMM_OUTDIR" ]; then
    echo "Error: LKMM_OUTDIR not set. Run 'config' and 'run' first."
    exit 1
  fi

  CAT_FILE="${1:?Usage: $0 modelcheck <cat-file>}"

  MC_LOGS="$LKMM_OUTDIR/../dartagnan-logs"
  mkdir -p "$MC_LOGS"

  echo "Running dartagnan model checker..."
  python3 "$SCRIPT_DIR/run_dartagnan.py" "$LKMM_OUTDIR" "$CAT_FILE" "$LKMM_OUTDIR/EMPTY" "$MC_LOGS"

  echo "Generating model checker CSV..."
  if [ "$KARCH" = "arm64" ]; then
    MC_CSV_NAME="arm"
  else
    MC_CSV_NAME="$KARCH"
  fi
  python3 "$SCRIPT_DIR/logs2csv.py" "$MC_LOGS" "$LKMM_OUTDIR/../$MC_CSV_NAME.csv"
}

if [ -z "$1" ]; then
  echo "Usage: $0 <config|run|modelcheck|klitmus>"
  exit 1
fi

if [ "$1" = "config" ]; then
  mkConfig
elif [ "$1" = "donfig" ]; then
  mkDebugConfig
elif [ "$1" = "run" ]; then
  setupResult
  doBuild
elif [ "$1" = "debug" ]; then
  setupResult
  debugBuild
elif [ "$1" = "modelcheck" ]; then
  doModelCheck "$2"
elif [ "$1" = "klitmus" ]; then
  kernel_litmus
else
  echo "Unknown command: $1"
  exit 1
fi
