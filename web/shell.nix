with import <nixpkgs> {};

emscriptenStdenv.mkDerivation {
  name = "somegames-web";
  src = ./.;

  buildInputs = [
    cmake
    python3Packages.httpserver
    emscripten
    nodejs
    # emscriptenPackages.zlib
  ];

}

