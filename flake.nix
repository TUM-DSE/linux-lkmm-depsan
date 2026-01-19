{
  description = "Linux for LKMM DepSan";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    clang-unwrapped = {
      url = "file://.";
      flake = false;
    };
    dartagnan = {
      url = "github:ReimersS/Dat3M?ref=nixify";
    };
  };
  outputs = { self, nixpkgs, flake-utils, clang-unwrapped, dartagnan, ...}:
  flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs { inherit system; };
      my-llvm = pkgs.stdenv.mkDerivation {
        name = "impure-clang";
        src = null;
        dontUnpack = true;
        installPhase = ''
          mkdir -p $out/bin
          for bin in ${toString (builtins.attrNames (builtins.readDir (clang-unwrapped.outPath+"/build/bin/")))}; do
          cat > $out/bin/$bin <<EOF
          #!${pkgs.runtimeShell}
          exec "$(cat ${clang-unwrapped.outPath+"/.pwd"})/build/bin/$bin" "\$@"
          EOF
          chmod +x $out/bin/$bin
          done
        '';
        #passthru.isClang = true;
      };
      my-wrapped-llvm = pkgs.wrapCCWith rec {
          cc = my-llvm;
          libc = pkgs.stdenv.cc.libc;
          bintools = pkgs.wrapBintoolsWith {
            bintools = pkgs.llvmPackages.bintools-unwrapped;
            libc = pkgs.stdenv.cc.libc;
          };
        };
      mystdenv = (pkgs.overrideCC pkgs.llvmPackages.stdenv my-wrapped-llvm);
    in
    {

      defaultPackage = pkgs.linux.override {
        stdenv = pkgs.llvmPackages.stdenv;
        src = self;
      };
      impurePackage = mystdenv.mkDerivation {
        name = "impure-linux-lkmm-depsan";
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
          dartagnan.packages.${system}.default
        ] ++ pkgs.linux.nativeBuildInputs;
        src = self;
        hardeningDisable = ["all"];
      };
    }
  );
}
