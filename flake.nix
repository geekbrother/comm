{
  description = "Comm flake";

  inputs = {
    utils.url = "github:numtide/flake-utils";
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
  };

  outputs = { self, nixpkgs, utils, ... }:
    let
      # put devShell and any other required packages into local overlay
      localOverlay = import ./nix/overlay.nix;
      overlays = [
        localOverlay
      ];

      pkgsForSystem = system: import nixpkgs {
        # if you have additional overlays, you may add them here
        inherit overlays system;
        config.android_sdk.accept_license = true;
      };
    # https://github.com/numtide/flake-utils#usage for more examples
    in utils.lib.eachSystem [ "x86_64-linux" "x86_64-darwin" "aarch64-darwin" ] (system: rec {
      legacyPackages = pkgsForSystem system;
      inherit (legacyPackages) devShell;
  }) // {
    inherit overlays;
    # unfortunately, nix flake check will error unless you have an explicit `final: prev:`
    overlay = final: prev: (nixpkgs.lib.composeManyExtensions overlays) final prev;
  };
}
