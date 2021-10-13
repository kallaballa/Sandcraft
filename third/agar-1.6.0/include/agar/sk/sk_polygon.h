/*	Public domain	*/

typedef struct sk_polygon {
	struct sk_node node;
	SK_Line *_Nonnull *_Nullable s;		/* Line boundaries */
	Uint flags;
	Uint n;
	M_Color color;				/* Fill color */
} SK_Polygon;

#define SKPOLYGON(n) ((SK_Polygon *)(n))

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC SK_NodeOps skPolygonOps;
extern DECLSPEC SK_Polygon *_Nonnull SK_PolygonNew(void *_Nonnull);
extern DECLSPEC SK_Polygon *_Nonnull SK_PolygonFromValue(void *_Nonnull, M_Polygon);
extern DECLSPEC void SK_PolygonInit(void *_Nonnull, Uint);
extern DECLSPEC int SK_PolygonLoad(SK *_Nonnull, void *_Nonnull, AG_DataSource *_Nonnull);
extern DECLSPEC int SK_PolygonSave(SK *_Nonnull, void *_Nonnull, AG_DataSource *_Nonnull);
extern DECLSPEC void SK_PolygonDraw(void *_Nonnull, struct sk_view *_Nonnull);
extern DECLSPEC M_Real SK_PolygonProximity(void *_Nonnull, const M_Vector3 *_Nonnull, M_Vector3 *_Nonnull);
extern DECLSPEC int SK_PolygonDelete(void *_Nonnull);
extern DECLSPEC void SK_PolygonWidth(SK_Polygon *_Nonnull, M_Real);
extern DECLSPEC void SK_PolygonColor(SK_Polygon *_Nonnull, M_Color);
extern DECLSPEC M_Polygon SK_PolygonValue(SK_Polygon *_Nonnull);
extern DECLSPEC Uint SK_PolygonAddSide(SK_Polygon *_Nonnull, SK_Line *_Nonnull);
__END_DECLS
/* Close generated block */
