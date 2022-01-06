# Motivation

Nix allows for cross platform and language package management. This lessens the burden on developers trying to get the exact dependencies to be productive. Nix packages live outside of the host system, so the packages are free deviate as needed.

For how nix package management works, please refer to the official [how Nix works guide](https://nixos.org/guides/how-nix-works.html).

# Requirements

To set up a dev environment using Nix, you will need a macOS or Linux machine.

# Prerequisites

## Nix package manager

Go to the NixOS website to install the Nix package manager for [macOS](https://nixos.org/download.html#nix-install-macos) or [Linux](https://nixos.org/download.html).

Nix needs to create a `/nix` directory, and install the initial Nix store and binaries. The installation script guides you through the setup process with minimal interaction.

If you’d like to audit the script to alleviate any security concern, you can view it [here](https://nixos.org/nix/install).

# Configuration

## Nix Flakes

[Nix Flakes](https://nixos.wiki/wiki/Flakes) are the new canonical way to expose Nix packages. The [exposed packages](https://nixos.wiki/wiki/Flakes#Output_schema) can be normal Nix packages, [overlays](https://nixos.wiki/wiki/Overlays), [modules](https://nixos.wiki/wiki/Module), or even [entire systems](https://nixos.wiki/wiki/Flakes#Using_nix_flakes_with_NixOS). The `flake.nix` file is used to communicate what is exposed and the `flake.lock` file is used to ensure that all dependencies are captured in an immutable fashion.

You will need to edit the Nix configuration file to enable Nix Flakes.

```
sudo vim /etc/nix/nix.conf
```

Add the following line to the file:

```
experimental-features = nix-command flakes
```

# Development

Run `nix develop` to create a dev environment. Nix installs packages in the Nix store, but your system wont be aware of the packages until they are introduced to either the system or shell in some manner. `nix develop` spawns a shell and brings these packages into scope.
