{ stdenv
, lib
, cmake
, fetchFromGitHub
}:

stdenv.mkDerivation rec {
  pname = "amqp-cpp";
  version = "4.3.16";

  src = fetchFromGitHub {
    owner = "CopernicaMarketingSoftware";
    repo = "amqp-cpp";
    rev = "v${version}";
    sha256 = "sha256-aBLNdw9LhHFwnIt70vIYlX1/j2IUTmpm5Ub+ZImF8FI=";
  };

  nativeBuildInputs = [
    cmake
  ];

  cmakeFlagsArray = lib.optionals (stdenv.isLinux || stdenv.isDarwin) [
    "-DAMQP-CPP_BUILD_SHARED=ON"
  ] ++ lib.optionals stdenv.isLinux [
    "-DAMQP-CPP_LINUX_TCP=ON"
  ];
}

