#/bin/bash

cd third/guichan-0.8.2; make clean; emconfigure ./configure --disable-opengl --enable-force-sdl --enable-force-sdlimage && emmake make $@
