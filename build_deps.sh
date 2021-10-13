#/bin/bash

cd third/guichan-0.8.2; make clean; ./configure --disable-opengl && make $@
