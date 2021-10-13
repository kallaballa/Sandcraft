#/bin/bash

sudo id > /dev/null
cd third/agar-1.6.0 
make clean 
CFLAGS="-msimd128 -DNDEBUG -g0 -O3 -ffp-contract=fast -freciprocal-math -fno-signed-zeros --closure 1 -s USE_FREETYPE=1 -s USE_LIBPNG=1" LDFLAGS="-s WASM_BIGINT -s MALLOC=emmalloc -s STACK_OVERFLOW_CHECK=0 -s ASSERTIONS=0 -s SAFE_HEAP=0 --closure 1 -menable-unsafe-fp-math -s USE_FREETYPE=1 -s USE_LIBPNG=1" emconfigure ./configure --with-sdl --without-x --without-glx --without-xinerama --with-png --without-jpeg --without-gl --with-fontconfig --with-freetype --without-portaudio --without-sndfile --without-db4 --disable-network --enable-gui
emmake make -j8 depend all && sudo make install
