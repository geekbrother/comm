# Nix development environment

This is a guide to quickly create a development environment using Nix for Linux or Darwin (macOS).

## Prerequisites

### Install Nix

macOS: https://nixos.org/download.html#nix-install-macos
Linux: https://nixos.org/download.html
NixOS: You're already done! :)

Nix needs to create a `/nix` directory, and install the initial nix store and binaries.
The installation script guides you through the setup process with minimal interaction.

If you'd like to audit the script to alleviate any security concern, you can view it here: [installation script](https://nixos.org/nix/install).
Care was given to ensure that the script is very readable (as much as
bash can be, at least).

### Nix Flakes

[Nix Flakes](https://nixos.wiki/wiki/Flakes) are the new canonical way of exposing and working with nix.
The flake is meant to provide a uniform way for interfacing between different nix-capable repositories.
In addition, we can easily pin inputs by checking the generated [F/f]lake lock file into the repo.

[Directions to enable Flakes for non-NixOS can be found here](https://nixos.wiki/wiki/Flakes#Non-NixOS).
In summary though, you will need to add the following line to your `/etc/nix/nix.conf`

```bash
$ sudo vim /etc/nix/nix.conf

# add the following line
experimental-features = nix-command flakes


# save and quit, :wq
```

## Nix development Shell

Nix is able to modify your shell per-project to include the needed dependencies by running:
```bash
nix develop
```

To exit the development shell, you may either enter `exit` or press `CTRL+D`.

### Direnv integration (Optional)

It's recommended to use the nix shell in conjunction with [`direnv`](https://github.com/direnv/direnv). This will
allow you to load and unload the development shell upon entering the directory. If you require certain
environment variables to be set upon entering, direnv will most likely be a welcome quality-of-life change.

Direnv is available through many package managers, please visit [installation instructions](https://github.com/direnv/direnv/blob/master/docs/installation.md) for each supported package manager. With nix, it may be installed as `nix-env -iA nixpkgs.direnv`.

Hooking into a shell is dependent on a specific shell, please follow [the official documenation](https://github.com/direnv/direnv/blob/master/docs/hook.md). Hooking allows for direnv to be triggered on each directory change
to determine if it should react. Without a shell hook, direnv will be unaware of changes in your shell.

## How Nix Works

This section will attempt to give an intuition around how nix works, but will not be comprehensive.

The problem that nix tries to solve is capturing all of the inputs need to create a package. This includes
but is not limited to: sources, patches, dependencies (direct and transitive), environment variables,
configure flags, build flags, build and installation commands, etc. Nix takes all of the inputs
of a package and reflects it in how it's addressed. This gives a unique name for every possible
"derivation" of a package. This is how nix works. It first creates the "derivation", which can
be thought of as the build "recipe" to create a package. When asked, nix will also "realise" these
"derivations" into the more tangible form.

Nix installs packages, file contents, binaries, configurations into a central location: the nix store.
These packages will have a path like `/nix/store/c24460c0iw7kai6z5aan6mkgfclpl2qj-hello-2.10`.
In this example, `/nix/store/` is the location of the nix store, `c24460c0iw7kai6z5aan6mkgfclpl2qj`
is a cryptographic hash (alluded to from above), and `hello-2.10` is the derivation name (package name + version).

The contents of a package will depend on the package, in the gnu hello example it is:
```
$ tree /nix/store/c24460c0iw7kai6z5aan6mkgfclpl2qj-hello-2.10
/nix/store/c24460c0iw7kai6z5aan6mkgfclpl2qj-hello-2.10
|-- bin
|   `-- hello
`-- share
    |-- info
    |   `-- hello.info
    `-- man
        `-- man1
            `-- hello.1.gz
```

Here, the hello binary was installed under the bin directory, and can be directly invoked:
```bash
$ /nix/store/c24460c0iw7kai6z5aan6mkgfclpl2qj-hello-2.10/bin/hello -g "Hello from Comm"
Hello from Comm
```

## How to use Nix

Nix can be used to bring in dependencies, or package software. For creating a development
environment, you may use `nix-shell` or `nix develop`. Nix only "installs" packages
into the nix store, but your system wont be aware of the packages until they are
introduced to either the system or shell in some manner. `Nix-shell` and `nix develop`
both work by determing the nix packages, and then modifying the PATH, XDG_DATA_DIR, and
toolchain variables such as: PKG_CONFIG_PATH or CMAKE_MODULE_PATH. 

For packaging software, you will
need to package it using the nix language. Since nix "retains" all notions of dependencies
for a given package, you can export the package as a docker file, iso, vm image, and many
other formats.
