/*	Public domain	*/

typedef struct vg_polygon {
	struct vg_node _inherit;
	int outline;				/* Render outline? */
	Uint                         nPts;
	VG_Point *_Nullable *_Nonnull pts;	/* Vertices */

	int  *_Nullable ints;	/* Sorted intersections (for FB rendering) */
	Uint           nInts;
	Uint32 _pad;
} VG_Polygon;

#define VGPOLYGON(p) ((VG_Polygon *)(p))

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC VG_NodeOps vgPolygonOps;
extern DECLSPEC VG_Polygon *_Nonnull VG_PolygonNew(void *_Nullable);
extern DECLSPEC void VG_PolygonSetOutline(VG_Polygon *_Nonnull, int);
extern DECLSPEC Uint VG_PolygonVertex(VG_Polygon *_Nonnull, VG_Point *_Nonnull);
extern DECLSPEC void VG_PolygonDelVertex(VG_Polygon *_Nonnull, Uint);
__END_DECLS
/* Close generated block */
