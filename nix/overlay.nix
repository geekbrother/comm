# `final` refers the package set with all overlays applied.
# This allows for added or modified packages to be referenced with
# all relevant changes applied
final:

# `prev` refers to the previous package set before this current overlay is applied.
# This is cheaper for nix to evaluate, thus should be prefered over final.
prev:

{
  # add packages meant for just this repository
  devShell = final.callPackage ./dev-shell.nix { };
}
