/*	Public domain	*/

typedef struct vg_circle {
	struct vg_node _inherit;	/* VG_Node(3) -> VG_Circle */
	VG_Point *_Nullable p;		/* Centerpoint */
	double r;			/* Radius */
} VG_Circle;

#define VGCIRCLE(p) ((VG_Circle *)(p))

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC VG_NodeOps vgCircleOps;
extern DECLSPEC VG_Circle *_Nonnull VG_CircleNew(void *_Nullable, VG_Point *_Nonnull, float);
extern DECLSPEC void VG_CircleCenter(VG_Circle *_Nonnull, VG_Point *_Nonnull);
__END_DECLS
/* Close generated block */
