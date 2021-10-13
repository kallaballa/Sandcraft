/*	Public domain	*/

typedef struct sk_pixmap {
	struct sk_node node;
	SK_Point *_Nullable p;		/* Center point */
	M_Real w, h;			/* Dimensions */
	M_Real alpha;			/* Overall alpha */
	int s;				/* Mapped surface */
	Uint32 _pad;
	AG_Surface *_Nullable sSrc;	/* Source surface */
} SK_Pixmap;

#define SK_PIXMAP(n) ((SK_Pixmap *)(n))

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC SK_NodeOps skPixmapOps;
extern DECLSPEC SK_Pixmap *_Nonnull SK_PixmapNew(void *_Nonnull, SK_Point *_Nullable);
extern DECLSPEC void SK_PixmapInit(void *_Nonnull, Uint);
extern DECLSPEC void SK_PixmapDestroy(void *_Nonnull);
extern DECLSPEC int SK_PixmapLoad(SK *_Nonnull, void *_Nonnull, AG_DataSource *_Nonnull);
extern DECLSPEC int SK_PixmapSave(SK *_Nonnull, void *_Nonnull, AG_DataSource *_Nonnull);
extern DECLSPEC void SK_PixmapDraw(void *_Nonnull, struct sk_view *_Nonnull);
extern DECLSPEC void SK_PixmapEdit(void *_Nonnull, struct ag_widget *_Nonnull, struct sk_view *_Nonnull);
extern DECLSPEC M_Real SK_PixmapProximity(void *_Nonnull, const M_Vector3 *_Nonnull, M_Vector3 *_Nonnull);
extern DECLSPEC int SK_PixmapDelete(void *_Nonnull);
extern DECLSPEC int SK_PixmapMove(void *_Nonnull, const M_Vector3 *_Nonnull, const M_Vector3 *_Nonnull);
extern DECLSPEC SK_Status SK_PixmapConstrained(void *_Nonnull);
extern DECLSPEC void SK_PixmapDimensions(SK_Pixmap *_Nonnull, M_Real, M_Real);
extern DECLSPEC void SK_PixmapAlpha(SK_Pixmap *_Nonnull, M_Real);
extern DECLSPEC void SK_PixmapSurface(SK_Pixmap *_Nonnull, AG_Surface *_Nullable);
__END_DECLS
/* Close generated block */
