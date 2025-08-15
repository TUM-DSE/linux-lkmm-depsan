{
  description = "Linux for LKMM DepSan";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };
  outputs = { self, nixpkgs, flake-utils, ...}:
  flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs { inherit system; };
      my-llvm = pkgs.stdenv.mkDerivation {
        name = "impure-clang";
        dontUnpack = true;
        installPhase = ''
          mkdir -p $out/bin
          for bin in ${toString (builtins.attrNames (builtins.readDir (pkgs.llvmPackages.clang-unwrapped.outPath + "/bin")))}; do
          cat > $out/bin/$bin <<EOF
          #!${pkgs.runtimeShell}
          exec "../llvm-lkmm-depsan/build/bin/$bin" "\$@"
          EOF
          chmod +x $out/bin/$bin
          done
        '';
        passthru.isClang = true;
      };
      my-wrapped-llvm = pkgs.wrapCCWith rec {
          cc = my-llvm;
          bintools = pkgs.llvmPackages.bintools;
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
        buildInputs = pkgs.linux.buildInputs;
        nativeBuildInputs = pkgs.linux.nativeBuildInputs ++ [ pkgs.gdb ];
        src = self;
      };
    }
  );
}
