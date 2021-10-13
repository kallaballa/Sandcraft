/*	Public domain	*/

typedef struct sk_arc {
	struct sk_node node;
	SK_Point *_Nullable p;		/* Center point of circle */
	SK_Point *_Nullable e1;		/* Endpoint #1 */
	SK_Point *_Nullable e2;		/* Endpoint #2 */
	M_Real  r;			/* Radius of circle */
	M_Color color;			/* Display color */
} SK_Arc;

#define SKARC(n) ((SK_Arc *)(n))

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC SK_NodeOps skArcOps;
extern DECLSPEC SK_Arc *_Nonnull SK_ArcNew(void *_Nonnull);
extern DECLSPEC void SK_ArcInit(void *_Nonnull, Uint);
extern DECLSPEC int SK_ArcLoad(SK *_Nonnull, void *_Nonnull, AG_DataSource *_Nonnull);
extern DECLSPEC int SK_ArcSave(SK *_Nonnull, void *_Nonnull, AG_DataSource *_Nonnull);
extern DECLSPEC void SK_ArcDraw(void *_Nonnull, struct sk_view *_Nonnull);
extern DECLSPEC M_Real SK_ArcProximity(void *_Nonnull, const M_Vector3 *_Nonnull, M_Vector3 *_Nonnull);
extern DECLSPEC void SK_ArcWidth(SK_Arc *_Nonnull, M_Real);
extern DECLSPEC void SK_ArcColor(SK_Arc *_Nonnull, M_Color);
__END_DECLS
/* Close generated block */
