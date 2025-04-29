#!/bin/sh

emcmake cmake -B build 
cmake --build build 
mkdir public
cp static/* public/
cp build/somegames-web.* public/

