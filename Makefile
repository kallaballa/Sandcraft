CXX      := g++
CXXFLAGS := -std=c++17 -pedantic -Wall -Wno-gnu-anonymous-struct -Wno-nested-anon-types
#-fno-exceptions
#LDFLAGS  := -L/opt/local/lib 
LIBS     := -lm
.PHONY: all release debian-release info debug clean debian-clean distclean asan shrink
ESTDIR := /
PREFIX := /usr/local
MACHINE := $(shell uname -m)
UNAME_S := $(shell uname -s)
LIBDIR := lib

UNAME_P := $(shell uname -p)

ifeq ($(UNAME_P),x86_64)
LIBDIR = lib64
endif

ifeq ($(UNAME_S), Darwin)
 LDFLAGS += -L/opt/X11/lib/
endif

ifndef TIMETRACK
CXXFLAGS += -D_NO_TIMETRACK
endif

ifdef NOTHREADS
CXXFLAGS += -D_NO_THREADS
endif

ifdef JAVASCRIPT_MT
JAVASCRIPT=1
CXXFLAGS += -D_JAVASCRIPT_MT -s USE_PTHREADS=1 -pthread
LDFLAGS += -D_JAVASCRIPT_MT -s USE_PTHREADS=1 -pthread -s PTHREAD_POOL_SIZE=navigator.hardwareConcurrency
endif

ifdef JAVASCRIPT
CXX	:= em++
EMCXXFLAGS = -D_JAVASCRIPT -D_NO_STACKTRACE -flto -I../third/datachannel-wasm/wasm/include/
#EMCXXFLAGS +=  -s DISABLE_EXCEPTION_CATCHING=1
ifndef JAVASCRIPT_MT
EMCXXFLAGS += -D_NO_THREADS -s DYNCALLS=1
endif
EMLDFLAGS += -L../third/datachannel-wasm/build/ -s INITIAL_MEMORY=419430400 -s TOTAL_STACK=52428800 -s WASM_BIGINT -s "EXPORTED_FUNCTIONS=['_load_image', '_main' ]" -s EXPORTED_RUNTIME_METHODS='["ccall","dynCall"]' -s FORCE_FILESYSTEM=1 -s STB_IMAGE=1 -s USE_SDL_IMAGE=1 -s USE_SDL_TTF=1 -s USE_LIBPNG=1 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s DYNCALLS=1

ifdef AUTOVECTOR
EMCXXFLAGS += -msimd128
endif

CXXFLAGS += $(EMCXXFLAGS) -c
LDFLAGS += $(EMLDFLAGS)
endif

ifdef AUTOVECTOR
CXXFLAGS += -D_AUTOVECTOR
endif

ifdef X86
CXXFLAGS += -m32
LDFLAGS += -L/usr/lib -m32 -static-libgcc -m32 -Wl,-Bstatic
endif

ifdef STATIC
LDFLAGS += -static-libgcc -Wl,-Bstatic
endif

all: release

ifneq ($(UNAME_S), Darwin)
release: LDFLAGS += -s
endif
ifdef JAVASCRIPT
release: LDFLAGS += -s STACK_OVERFLOW_CHECK=2 -s ASSERTIONS=0 -s SAFE_HEAP=0
endif
release: CXXFLAGS += -g0 -O3 -c
release: dirs

shrink: CXXFLAGS += -Os -w
shrink: LDFLAGS += -s
shrink: dirs

info: CXXFLAGS += -g3 -O0
info: LDFLAGS += -Wl,--export-dynamic -rdynamic
info: dirs

ifndef JAVASCRIPT
debug: CXXFLAGS += -rdynamic
debug: LDFLAGS += -rdynamic
endif
debug: CXXFLAGS += -g3 -O0
debug: LDFLAGS += -Wl,--export-dynamic
debug: dirs

profile: CXXFLAGS += -g3 -O3 
profile: LDFLAGS += -Wl,--export-dynamic
ifdef JAVASCRIPT
profile: LDFLAGS += --profiling
profile: CXXFLAGS += --profiling
endif
ifndef AMIGA
ifndef JAVASCRIPT
profile: CXXFLAGS += -rdynamic
endif
endif
profile: dirs

ifdef JAVASCRIPT
hardcore: CXXFLAGS += -DNDEBUG -g0 -O3 -ffp-contract=fast -freciprocal-math -fno-signed-zeros --closure 1 
hardcore: LDFLAGS += -s STACK_OVERFLOW_CHECK=0 -s ASSERTIONS=0 -s SAFE_HEAP=0 --closure 1 -menable-unsafe-fp-math
else
hardcore: CXXFLAGS += -DNDEBUG -g0 -Ofast
endif
#ifeq ($(UNAME_S), Darwin)
hardcore: LDFLAGS += -s
#endif
hardcore: dirs

ifdef JAVASCRIPT
asan: CXXFLAGS += -fsanitize=address
asan: LDFLAGS += -s STACK_OVERFLOW_CHECK=2 -s ASSERTIONS=2 -s NO_DISABLE_EXCEPTION_CATCHING=1 -s EXCEPTION_DEBUG=1 -fsanitize=address
else
asan: CXXFLAGS += -rdynamic -fsanitize=address
asan: LDFLAGS += -rdynamic -fsanitize=address
endif
asan: CXXFLAGS += -g3 -O0 -fno-omit-frame-pointer
asan: LDFLAGS += -Wl,--export-dynamic 
ifndef JAVASCRIPT
asan: LIBS+= -lbfd -ldw
endif
asan: dirs

clean: dirs

export LDFLAGS
export CXXFLAGS
export LIBS

dirs:
	${MAKE} -C src/ ${MAKEFLAGS} CXX=${CXX} ${MAKECMDGOALS}

debian-release:
	${MAKE} -C src/ -${MAKEFLAGS} CXX=${CXX} release
	
debian-clean:
	${MAKE} -C src/ -${MAKEFLAGS} CXX=${CXX} clean
	
install: ${TARGET}
	true
	
distclean:
	true
