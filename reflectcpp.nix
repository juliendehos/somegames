{ stdenv 
, cmake
}:

stdenv.mkDerivation {
  name = "reflect-cpp";

  src = fetchTarball 
    "https://github.com/getml/reflect-cpp/archive/refs/tags/v0.18.0.tar.gz";

    buildInputs = [
      cmake
    ];

}


