TARGET  := sandcraft

ifdef JAVASCRIPT
TARGET := sandcraft.js
endif

ifdef JAVASCRIPT_MT
TARGET := sandcraft.js
endif

SRCS  := main.cpp CmdLine.cpp Palette.cpp Config.cpp GameState.cpp Particles.cpp Renderer.cpp SDLHelper.cpp Utils.cpp Scene.cpp Error.cpp Slots.cpp WebsocketClient.cpp WebRTC.cpp


ifndef AMIGA
CXXFLAGS += `pkg-config --cflags sdl` `agar-config --cflags`
LIBS += `pkg-config --libs sdl` `agar-config --libs`
else
LIBS += -lSDL -ldebug
endif

ifndef AMIGA
ifndef JAVASCRIPT
ifndef JAVASCRIPT_MT
CXXFLAGS += `pkg-config --cflags SDL_image x11 freetype2 fontconfig libpng`
LIBS += `pkg-config --libs SDL_image x11 freetype2 fontconfig libpng`
endif
endif
endif

ifdef JAVASCRIPT_MT
LDFLAGS += --js-library ../third/datachannel-wasm/wasm/js/webrtc.js
LIBS += -ldatachannel-wasm -lwebsocket.js
endif

#precompiled headers
HEADERS := 

GCH     := ${HEADERS:.h=.gch}
OBJS    := ${SRCS:.cpp=.o} 
DEPS    := ${SRCS:.cpp=.dep} 

.PHONY: all release debug clean distclean 

all: release
release: ${TARGET}
debug: ${TARGET}
info: ${TARGET}
profile: ${TARGET}
hardcore: ${TARGET}
asan: ${TARGET}
shrink: ${TARGET}
assembler: ${TARGET}

${TARGET}: ${OBJS} 
	${CXX} ${LDFLAGS} -o $@ $^ ${LIBS} 

${OBJS}: %.o: %.cpp %.dep ${GCH}
	${CXX} ${CXXFLAGS} -o $@ -c $< 

${DEPS}: %.dep: %.cpp Makefile 
	${CXX} ${CXXFLAGS} -MM $< > $@ 

${GCH}: %.gch: ${HEADERS} 
	${CXX} ${CXXFLAGS} -o $@ -c ${@:.gch=.h}

install:
	mkdir -p ${DESTDIR}/${PREFIX}
	cp ${TARGET} ${DESTDIR}/${PREFIX}

uninstall:
	rm ${DESTDIR}/${PREFIX}/${TARGET}

clean:
	rm -f *~ ${DEPS} ${OBJS} ${GCH} ${TARGET} 

distclean: clean



