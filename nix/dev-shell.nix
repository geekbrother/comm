{ mkShell
, stdenv
, lib
, arcanist
, darwin
, nodejs-16_x
, openjdk11
, protobuf3_15
, yarn
}:

mkShell rec {

  # programs which are meant to be executed should go here
  nativeBuildInputs = [
    arcanist
    nodejs-16_x
    protobuf3_15
    yarn
  ];

  # include any libraries or programs in buildInputs
  buildInputs = [
    protobuf3_15
  ] ++ lib.optionals stdenv.isDarwin (with darwin.apple_sdk.frameworks; [
    CoreFoundation
    Security
  ]);

  # shell commands to be ran upon entering shell
  shellHook = ''
    # For NixOS, the pre-compiled binaries from npm will not be able to find
    # the c++ libraries, so we set them on LD_LIBRARY_PATH
    if [ -f /etc/NIXOS ]; then
      export LD_LIBRARY_PATH=${stdenv.cc.cc.lib}/lib
    fi

    echo "Welcome to Comm dev environment! :)"
  '';
}
