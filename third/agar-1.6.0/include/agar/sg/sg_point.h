/*	Public domain	*/

typedef struct sg_point {
	struct sg_geom _inherit;	/* SG_Geom -> SG_Point */
	float size;
	Uint8 _pad[12];
} SG_Point;

#define SGPOINT(n) ((SG_Point *)(n))

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC SG_NodeClass sgPointClass;
extern DECLSPEC SG_Point *_Nonnull SG_PointNew(void *_Nullable, const char *_Nullable, const M_Vector3 *_Nullable);
extern DECLSPEC void SG_PointSize(void *_Nonnull, M_Real);
#define SG_PointColor(pt,c) SG_GeomColor(SGGEOM(pt),(c))
__END_DECLS
/* Close generated block */
