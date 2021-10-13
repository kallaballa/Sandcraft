/*	Public domain	*/

typedef struct vg_point {
	struct vg_node _inherit;	/* VG_Node(3) -> VG_Point */
	double size;			/* Size in pixels (0.0 = invisible) */
} VG_Point;

#define VGPOINT(p) ((VG_Point *)(p))

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC VG_NodeOps vgPointOps;
extern DECLSPEC VG_Point *_Nonnull VG_PointNew(void *_Nullable, VG_Vector);
extern DECLSPEC void VG_PointSize(VG_Point *_Nonnull, double);
__END_DECLS
/* Close generated block */
