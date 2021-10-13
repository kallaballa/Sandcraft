#ifndef SRC_SDL_EMSCRIPTEN_HPP_
#define SRC_SDL_EMSCRIPTEN_HPP_

#include <cstddef>
#include <cstring>
#include <SDL/SDL.h>
extern "C" {
void* SDL_memset(void* dst, int c, size_t n) {
	return memset(dst, c, n);
}

void* SDL_memcpy(void* dst, const void* src, size_t n) {
	return memcpy(dst, src, n);
}

SDL_bool SANDCRAFT_SDL_IntersectRect(const SDL_Rect *A, const SDL_Rect *B, SDL_Rect *intersection)
{
	int Amin, Amax, Bmin, Bmax;

	/* Horizontal intersection */
	Amin = A->x;
	Amax = Amin + A->w;
	Bmin = B->x;
	Bmax = Bmin + B->w;
	if(Bmin > Amin)
	        Amin = Bmin;
	intersection->x = Amin;
	if(Bmax < Amax)
	        Amax = Bmax;
	intersection->w = Amax - Amin > 0 ? Amax - Amin : 0;

	/* Vertical intersection */
	Amin = A->y;
	Amax = Amin + A->h;
	Bmin = B->y;
	Bmax = Bmin + B->h;
	if(Bmin > Amin)
	        Amin = Bmin;
	intersection->y = Amin;
	if(Bmax < Amax)
	        Amax = Bmax;
	intersection->h = Amax - Amin > 0 ? Amax - Amin : 0;

	return (intersection->w && intersection->h) ? SDL_TRUE : SDL_FALSE;
}

static int SANDCRAFT_SDL_FillRect1(SDL_Surface *dst, SDL_Rect *dstrect,
		Uint32 color) {
	/* FIXME: We have to worry about packing order.. *sigh* */
	SDL_SetError("1-bpp rect fill not yet implemented");
	return -1;
}

static int SANDCRAFT_SDL_FillRect4(SDL_Surface *dst, SDL_Rect *dstrect,
		Uint32 color) {
	/* FIXME: We have to worry about packing order.. *sigh* */
	SDL_SetError("4-bpp rect fill not yet implemented");
	return -1;
}

/*
 * This function performs a fast fill of the given rectangle with 'color'
 */
int SANDCRAFT_SDL_FillRect(SDL_Surface *dst, SDL_Rect *dstrect, Uint32 color) {
	int x, y;
	Uint8 *row;

	/* This function doesn't work on surfaces < 8 bpp */
	if (dst->format->BitsPerPixel < 8) {
		switch (dst->format->BitsPerPixel) {
			case 1:
				return SANDCRAFT_SDL_FillRect1(dst, dstrect, color);
				break;
			case 4:
				return SANDCRAFT_SDL_FillRect4(dst, dstrect, color);
				break;
			default:
				SDL_SetError("Fill rect on unsupported surface format");
				return (-1);
				break;
		}
	}

	if (dstrect) {
		/* Perform clipping */
		if (!SANDCRAFT_SDL_IntersectRect(dstrect, &dst->clip_rect, dstrect)) {
			return (0);
		}
	} else {
		dstrect = &dst->clip_rect;
	}

	row = (Uint8 *) dst->pixels + dstrect->y * dst->pitch
			+ dstrect->x * dst->format->BytesPerPixel;
	if (dst->format->palette || (color == 0)) {
		x = dstrect->w * dst->format->BytesPerPixel;
		if (!color && !((uintptr_t) row & 3) && !(x & 3) && !(dst->pitch & 3)) {
			int n = x >> 2;
			for (y = dstrect->h; y; --y) {
				SDL_memset4((Uint32*) row, 0, n);
				row += dst->pitch;
			}
		} else {
			{
				for (y = dstrect->h; y; y--) {
					SDL_memset(row, color, x);
					row += dst->pitch;
				}
			}
		}
	} else {
		switch (dst->format->BytesPerPixel) {
			case 2:
				for (y = dstrect->h; y; --y) {
					Uint16 *pixels = (Uint16 *) row;
					Uint16 c = (Uint16) color;
					Uint32 cc = (Uint32) c << 16 | c;
					int n = dstrect->w;
					if ((uintptr_t) pixels & 3) {
						*pixels++ = c;
						n--;
					}
					if (n >> 1)
						SDL_memset4((Uint32*) pixels, cc, n >> 1);
					if (n & 1)
						pixels[n - 1] = c;
					row += dst->pitch;
				}
				break;

			case 3:
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
				color <<= 8;
#endif
				for (y = dstrect->h; y; --y) {
					Uint8 *pixels = row;
					for (x = dstrect->w; x; --x) {
						SDL_memcpy(pixels, &color, 3);
						pixels += 3;
					}
					row += dst->pitch;
				}
				break;

			case 4:
				for (y = dstrect->h; y; --y) {
					SDL_memset4((Uint32*) row, color, dstrect->w);
					row += dst->pitch;
				}
				break;
		}
	}

	/* We're done! */
	return (0);
}

}

#endif /* SRC_SDL_EMSCRIPTEN_HPP_ */
