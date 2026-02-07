{
  description = "emath — C++20 Mathematics Library";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in {
        packages.default = pkgs.stdenv.mkDerivation {
          pname = "emath";
          version = "0.1.0";
          src = ./.;

          nativeBuildInputs = with pkgs; [ gcc gnumake ];

          buildPhase = ''
            make math.o
          '';

          installPhase = ''
            mkdir -p $out/include $out/lib
            cp -r include/* $out/include/
            cp math.o $out/lib/
          '';

          passthru.src-with-vendors = self;
        };

        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            gcc
            gnumake
            pkg-config
          ];

          shellHook = ''
            echo "emath development environment"
            echo "  Build: make math.o"
          '';
        };
      }
    );
}
