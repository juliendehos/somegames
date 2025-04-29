{ pkgs ? import <nixpkgs> {} }:

let
  reflectcpp = pkgs.callPackage ./reflectcpp.nix {};

in pkgs.stdenv.mkDerivation {
  name = "somegames";

  src = ./. ;

  buildInputs = with pkgs; [
    catch2
    cmake
    gtkmm4
    pkg-config
    reflectcpp
    wrapGAppsHook4
  ];

  shellHook = ''
    echo ${reflectcpp}
    echo ${pkgs.gtkmm4}
  '';

}

