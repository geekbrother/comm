prev: final: {
  # add packages meant for just this repository

  devShell = final.callPackage ./dev-shell.nix { };
}
