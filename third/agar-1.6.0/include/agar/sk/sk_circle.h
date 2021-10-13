/*	Public domain	*/

typedef struct sk_circle {
	struct sk_node node;
	SK_Point *_Nullable p;		/* Center point */
	M_Real  r;			/* Radius */
	M_Real  width;			/* Display thickness */
	Uint8 _pad[8];
	M_Color color;			/* Display color */
} SK_Circle;

#define SKCIRCLE(n) ((SK_Circle *)(n))

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC SK_NodeOps skCircleOps;
extern DECLSPEC SK_Circle *_Nonnull SK_CircleNew(void *_Nonnull);
extern DECLSPEC SK_Circle *_Nonnull SK_CircleFromValue(void *_Nonnull, M_Circle2);
extern DECLSPEC M_Circle2 SK_CircleValue(SK_Circle *_Nonnull);
extern DECLSPEC void SK_CircleInit(void *_Nonnull, Uint);
extern DECLSPEC int SK_CircleLoad(SK *_Nonnull, void *_Nonnull, AG_DataSource *_Nonnull);
extern DECLSPEC int SK_CircleSave(SK *_Nonnull, void *_Nonnull, AG_DataSource *_Nonnull);
extern DECLSPEC void SK_CircleDraw(void *_Nonnull, struct sk_view *_Nonnull);
extern DECLSPEC void SK_CircleEdit(void *_Nonnull, struct ag_widget *_Nonnull, struct sk_view *_Nonnull);
extern DECLSPEC M_Real SK_CircleProximity(void *_Nonnull, const M_Vector3 *_Nonnull, M_Vector3 *_Nonnull);
extern DECLSPEC int SK_CircleDelete(void *_Nonnull);
extern DECLSPEC int SK_CircleMove(void *_Nonnull, const M_Vector3 *_Nonnull, const M_Vector3 *_Nonnull);
extern DECLSPEC SK_Status SK_CircleConstrained(void *_Nonnull);
extern DECLSPEC void SK_CircleWidth(SK_Circle *_Nonnull, M_Real);
extern DECLSPEC void SK_CircleColor(SK_Circle *_Nonnull, M_Color);
__END_DECLS
/* Close generated block */
