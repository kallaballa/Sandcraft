#include "SDLHelper.hpp"

#include <iostream>
#include <cmath>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
namespace sandcraft {

SDLHelper::SDLHelper() {
	// Initializing SDL
	if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
		fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError());
		SDL_Quit();
	}

#ifndef _AMIGA
#ifndef __EMSCRIPTEN__
	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		fprintf( stderr, "SDL_Image initialization failed: %s\n",
				SDL_GetError());
		SDL_Quit();
	}
#endif
#endif

	for(size_t i = 0; i < SDL_NumJoysticks(); ++i) {
		SDL_JoystickOpen(i);
	}

//	SDL_ShowCursor(true);
#ifdef _AMIGA
	screen_ = SDL_SetVideoMode(cfg_.width_, cfg_.height_, 8, SDL_SWSURFACE | SDL_RESIZABLE);
#else
	screen_ = SDL_SetVideoMode(cfg_.width_, cfg_.height_ , 32, SDL_SWSURFACE);
#endif
	if (screen_ == NULL) {
		fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
	}
	SDL_EnableUNICODE(true);
	//Setting caption
	SDL_WM_SetCaption("Sandcraft", NULL);
	//Enabeling key repeats
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
}

void SDLHelper::set_pixel(Uint16 x, Uint16 y, Uint32 pixel) {
	Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) screen_->pixels
			+ y * screen_->pitch + x * screen_->format->BytesPerPixel);
	*target_pixel = pixel;
}

Uint32 SDLHelper::get_pixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}


#ifndef _AMIGA
SDL_Surface* SDLHelper::loadPng(std::string path) {
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
				IMG_GetError());
		return nullptr;
	} else {
#ifndef __EMSCRIPTEN__
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, screen_->format, 0);
		if (optimizedSurface == NULL) {
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(),
					SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
		return optimizedSurface;
#else
		return loadedSurface;
#endif
	}
}
#endif

Uint32 SDLHelper::hsvToRgb(float H, float S,float V) {
    if(H>360 || H<0 || S>100 || S<0 || V>100 || V<0){
    	printf("The givem HSV values are not in valid range");
        return 0;
    }
    float s = S/100;
    float v = V/100;
    float C = s*v;
    float X = C*(1-std::abs(fmod(H/60.0, 2)-1));
    float m = v-C;
    float r,g,b;
    if(H >= 0 && H < 60){
        r = C,g = X,b = 0;
    }
    else if(H >= 60 && H < 120){
        r = X,g = C,b = 0;
    }
    else if(H >= 120 && H < 180){
        r = 0,g = C,b = X;
    }
    else if(H >= 180 && H < 240){
        r = 0,g = X,b = C;
    }
    else if(H >= 240 && H < 300){
        r = X,g = 0,b = C;
    }
    else{
        r = C,g = 0,b = X;
    }
    Uint8 R = (r+m)*255;
    Uint8 G = (g+m)*255;
    Uint8 B = (b+m)*255;
    return SDL_MapRGB(screen_->format, R, G, B);
}



void SDLHelper::drawCursor(int x, int y) {
	SDL_Rect partHorizontal = { Sint16(x + 1), Sint16(y + 1), 4, 1 };
	SDL_Rect partVertical = { Sint16(x + 1), Sint16(y + 1), 1, 4 };

	SDL_FillRect(screen_, &partHorizontal,
			SDL_MapRGB(screen_->format, 255, 0, 255));
	SDL_FillRect(screen_, &partVertical,
			SDL_MapRGB(screen_->format, 255, 0, 255));
}

void SDLHelper::drawPenSize() {
	SDL_Rect size = { Sint16(screen_->w - cfg_.btn_size_), Sint16(
			screen_->h - cfg_.btn_size_ - 1), 0, 0 };

	switch (gs_.penSize_) {
	case 1:
		size.w = 1;
		size.h = 1;
		break;
	case 2:
		size.w = 2;
		size.h = 2;
		break;
	case 4:
		size.w = 3;
		size.h = 3;
		break;
	case 8:
		size.w = 5;
		size.h = 5;
		break;
	case 16:
		size.w = 7;
		size.h = 7;
		break;
	case 32:
		size.w = 9;
		size.h = 9;
		break;

	default:
		break;
	}

	SDL_FillRect(screen_, &size, SDL_MapRGB(screen_->format, 255, 255, 255));
}
}
