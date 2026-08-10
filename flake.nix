{
  description = "Linux for LKMM DepSan";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    llvm-lkmm-depsan = {
      url = "github:TUM-DSE/llvm-lkmm-depsan";
    };
    dartagnan = {
      url = "github:ReimersS/Dat3M?ref=depsan";
    };
  };
  outputs = { self, nixpkgs, flake-utils, llvm-lkmm-depsan, dartagnan, ...}:
  flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs { inherit system; };
      custom-clang = llvm-lkmm-depsan.packages.${system}.default;
      my-wrapped-llvm = pkgs.wrapCCWith rec {
          cc = custom-clang;
          libc = pkgs.stdenv.cc.libc;
          bintools = pkgs.wrapBintoolsWith {
            bintools = pkgs.llvmPackages.bintools-unwrapped;
            libc = pkgs.stdenv.cc.libc;
          };
        };
      mystdenv = (pkgs.overrideCC pkgs.llvmPackages.stdenv my-wrapped-llvm);
      python-env = pkgs.python3.withPackages (python-pkgs: [
        python-pkgs.pandas
        python-pkgs.seaborn
        python-pkgs.matplotlib
        python-pkgs.pylatex
        python-pkgs.zlib-ng
      ]);
      dat3m = dartagnan.packages.${system}.default;
      dat3m-cat = pkgs.stdenv.mkDerivation {
        name = "dat3m-cat-files";
        src = dartagnan;
        phases = [ "unpackPhase" "installPhase" ];
        installPhase = ''
          mkdir -p $out/cat
          cp -r cat/. $out/cat/
        '';
      };
      kernel-src = pkgs.stdenv.mkDerivation {
        name = "linux-lkmm-depcheck-src";
        src = self;
        phases = [ "unpackPhase" "installPhase" ];
        installPhase = ''
          mkdir -p $out/kernel-src
          cp -r . $out/kernel-src/
        '';
      };
    in
    {

      defaultPackage = pkgs.linux.override {
        stdenv = pkgs.llvmPackages.stdenv;
        src = self;
      };

      packages.container = pkgs.dockerTools.buildLayeredImage {
        name = "lkmm-depchecker-${if system == "aarch64-linux" || system == "aarch64-darwin" then "aarch64" else "x86-64"}";
        tag = "latest";
        contents = [
          pkgs.bashInteractive
          pkgs.coreutils
          pkgs.findutils
          pkgs.gnumake
          pkgs.gcc
          pkgs.gnugrep
          pkgs.gnused
          pkgs.gawk
          pkgs.diffutils
          pkgs.patch
          pkgs.perl
          pkgs.bc
          pkgs.flex
          pkgs.bison
          pkgs.elfutils
          pkgs.openssl
          pkgs.openssl.dev
          pkgs.pkg-config
          pkgs.dockerTools.usrBinEnv
          pkgs.dockerTools.caCertificates
          my-wrapped-llvm
          python-env
          kernel-src
          dat3m
          dat3m-cat
          pkgs.stdenv.cc.cc.lib
        ] ++ pkgs.linux.nativeBuildInputs;
        config = {
          Cmd = [ "${pkgs.writeShellScript "entrypoint.sh" ''
            set -e
            mkdir -p /tmp
            ln -sfn "${dat3m-cat}/cat" /cat
            KERNEL_STORE="${kernel-src}/kernel-src"
            BUILD_DIR="/build/linux"

            echo "=== DepSan Pipeline ==="

            if [ ! -d "$BUILD_DIR/scripts" ]; then
              echo "--- Copying kernel sources to $BUILD_DIR ---"
              mkdir -p "$BUILD_DIR"
              cp -r "$KERNEL_STORE"/. "$BUILD_DIR"/
              chmod -R u+w "$BUILD_DIR"
            fi

            SCRIPT_DIR="$BUILD_DIR/scripts/depsan"

            ARCH=$(uname -m)
            if [ "$ARCH" = "aarch64" ]; then
              KARCH="arm64"
            else
              KARCH="$ARCH"
            fi

            LOCAL_RESULTS="/build/output"
            export LKMM_OUTDIR="$LOCAL_RESULTS/results/$KARCH/latest"
            echo "Results will be written to: $LKMM_OUTDIR (local), then copied to /output"

            echo "--- Configuring kernel ---"
            "$SCRIPT_DIR/go.sh" config

            echo "--- Building kernel ---"
            "$SCRIPT_DIR/go.sh" run

            echo "--- Running model checker ---"
            CAT_FILE="${dat3m-cat}/cat/linux-kernel.cat"
            MC_LOGS="$LOCAL_RESULTS/dartagnan-logs"
            python3 "$SCRIPT_DIR/run_dartagnan.py" "$LKMM_OUTDIR" "$CAT_FILE" "$LKMM_OUTDIR/EMPTY" "$MC_LOGS"

            echo "--- Generating model checker CSV ---"
            if [ "$KARCH" = "arm64" ]; then
              MC_CSV_NAME="arm"
            else
              MC_CSV_NAME="$KARCH"
            fi
            python3 "$SCRIPT_DIR/logs2csv.py" "$MC_LOGS" "$LOCAL_RESULTS/$MC_CSV_NAME.csv"

            echo "--- Generating plots ---"
            python3 "$SCRIPT_DIR/plot.py" --results "$LOCAL_RESULTS" --arch "$KARCH" --outdir "$LOCAL_RESULTS/plots"

            echo "--- Copying results to /output ---"
            cp -r "$LOCAL_RESULTS"/. /output/

            if [ -n "''${OWNER_UID:-}" ]; then
              echo "--- Fixing output ownership to $OWNER_UID:''${OWNER_GID:-$OWNER_UID} ---"
              chown -R "$OWNER_UID:''${OWNER_GID:-$OWNER_UID}" /output
            fi

            echo "=== Done ==="
          ''}" ];
          Env = [
            "HOSTCC=${pkgs.gcc}/bin/gcc"
            "C_INCLUDE_PATH=${pkgs.openssl.dev}/include:${pkgs.elfutils.dev}/include"
            "LIBRARY_PATH=${pkgs.openssl.out}/lib"
            "LD_LIBRARY_PATH=${pkgs.stdenv.cc.cc.lib}/lib"
          ];
          Volumes = {
            "/output" = {};
          };
        };
      };

      devShells.default = mystdenv.mkDerivation {
        name = "linux-lkmm-depsan";
        shellHook = ''
          export HOSTCC="${pkgs.gcc}/bin/gcc"
        '';
        nativeBuildInputs = [
          pkgs.gdb
          pkgs.gcc
          pkgs.pkg-config
          (pkgs.python3.withPackages (python-pkgs: [
            python-pkgs.pandas
            python-pkgs.seaborn
            python-pkgs.matplotlib
            python-pkgs.notebook
            python-pkgs.pylatex
            python-pkgs.zlib-ng
          ]))
          dat3m
        ] ++ pkgs.linux.nativeBuildInputs;
        src = self;
        hardeningDisable = ["all"];
      };
    }
  );
}
