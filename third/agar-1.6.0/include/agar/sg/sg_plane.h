/*	Public domain	*/

typedef struct sg_plane {
	struct sg_geom _inherit;	/* SG_Geom -> SG_Plane */
} SG_Plane;

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC SG_NodeClass sgPlaneClass;
extern DECLSPEC SG_Plane *_Nonnull SG_PlaneNew(void *_Nullable, const char *_Nullable);
__END_DECLS
/* Close generated block */
