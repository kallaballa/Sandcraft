/*	Public domain	*/

#ifndef _AGAR_RG_PRIM_H_
#define _AGAR_RG_PRIM_H_
#include <agar/map/begin.h>

struct rg_tile;

enum rg_prim_blend_mode {
	RG_PRIM_OVERLAY_ALPHA,
	RG_PRIM_AVERAGE_ALPHA,
	RG_PRIM_SRC_ALPHA,
	RG_PRIM_DST_ALPHA,
};

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC void RG_ColorRGB(struct rg_tile *_Nonnull, const AG_Color *_Nonnull);
extern DECLSPEC void RG_ColorRGBA(struct rg_tile *_Nonnull, const AG_Color *_Nonnull);
extern DECLSPEC void RG_ColorHSV(struct rg_tile *_Nonnull, float,float,float);
extern DECLSPEC void RG_ColorHSVA(struct rg_tile *_Nonnull, float,float,float, Uint8);
extern DECLSPEC void RG_ColorUint32(struct rg_tile *_Nonnull, Uint32);
extern DECLSPEC void RG_BlendRGB(AG_Surface *_Nonnull, int,int, enum rg_prim_blend_mode, const AG_Color *_Nonnull);
extern DECLSPEC void RG_Circle2(struct rg_tile *_Nonnull, int,int, int);
extern DECLSPEC void RG_Line(struct rg_tile *_Nonnull, int,int, int,int);
extern DECLSPEC void RG_WuLine(struct rg_tile *_Nonnull, float,float, float,float);
extern DECLSPEC void RG_HLine(struct rg_tile *_Nonnull, int,int, int, Uint32);

static __inline__ void
RG_PutPixel(AG_Surface *_Nonnull su, int x, int y, Uint32 pc)
{
	Uint8 *dst;
	    
	if (x < 0 || y < 0 || (Uint)x >= su->w || (Uint)y >= su->h) {
		return;
	}
	dst = (Uint8 *)su->pixels + y*su->pitch + (x << 2);
	*(Uint32 *)dst = pc;
}
__END_DECLS
/* Close generated block */

#include <agar/map/close.h>
#endif	/* _AGAR_RG_PRIM_H_ */
