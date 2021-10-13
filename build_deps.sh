#/bin/bash

sudo id > /dev/null
cd third/agar-1.6.0 
make clean 
./configure --with-sdl --with-x --with-glx --without-xinerama --with-png --without-jpeg --without-gl --with-fontconfig --with-freetype --without-portaudio --without-sndfile --without-db4 --disable-network --enable-gui
make -j8 depend all && sudo make install
