/*	Public domain	*/

typedef struct sg_geom {
	struct sg_node _inherit;	/* SG_Node -> SG_Geom */
	Uint flags;
#define SG_GEOM_SAVED 0
	int stFactor;			/* Stipple Factor */
	M_Real wd;			/* Line Width */
	M_Color c;			/* Line Color */
	Uint16 stPat;			/* Stipple Pattern */
	Uint8 _pad[14];
} SG_Geom;

#define SGGEOM(n) ((SG_Geom *)(n))

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC SG_NodeClass sgGeomClass;
extern DECLSPEC SG_Geom *_Nonnull SG_GeomNew(void *_Nullable, const char *_Nullable, M_Geom3);
extern DECLSPEC void SG_GeomColor(SG_Geom *_Nonnull, M_Color);
extern DECLSPEC void SG_GeomLineWidth(SG_Geom *_Nonnull, M_Real);
extern DECLSPEC void SG_GeomLineStipple(SG_Geom *_Nonnull, int, Uint16);
extern DECLSPEC void SG_GeomDrawBegin(const SG_Geom *_Nonnull);
#define SG_GeomDrawEnd(geom) GL_PopAttrib()
__END_DECLS
/* Close generated block */
