/*	Public domain	*/

typedef struct sk_line {
	struct sk_node node;
	SK_Point *_Nullable p1;		/* Endpoint #1 */
	SK_Point *_Nullable p2;		/* Endpoint #2 */
	M_Real width;			/* Display width */
	Uint8 _pad[8];
	M_Color color;			/* Display color */
} SK_Line;

#define SKLINE(n) ((SK_Line *)(n))

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC SK_NodeOps skLineOps;
extern DECLSPEC SK_Line *_Nonnull SK_LineNew(void *_Nonnull);
extern DECLSPEC SK_Line *_Nonnull SK_LineFromValue(void *_Nonnull, M_Line2);
extern DECLSPEC M_Line2 SK_LineValue(const SK_Line *_Nonnull);
extern DECLSPEC void SK_LineInit(void *_Nonnull, Uint);
extern DECLSPEC int SK_LineLoad(SK *_Nonnull, void *_Nonnull, AG_DataSource *_Nonnull);
extern DECLSPEC int SK_LineSave(SK *_Nonnull, void *_Nonnull, AG_DataSource *_Nonnull);
extern DECLSPEC void SK_LineDraw(void *_Nonnull, struct sk_view *_Nonnull);
extern DECLSPEC void SK_LineEdit(void *_Nonnull, struct ag_widget *_Nonnull, struct sk_view *_Nonnull);
extern DECLSPEC M_Real SK_LineProximity(void *_Nonnull, const M_Vector3 *_Nonnull, M_Vector3 *_Nonnull);
extern DECLSPEC int SK_LineDelete(void *_Nonnull);
extern DECLSPEC int SK_LineMove(void *_Nonnull, const M_Vector3 *_Nonnull, const M_Vector3 *_Nonnull);
extern DECLSPEC SK_Status SK_LineConstrained(void *_Nonnull);
extern DECLSPEC void SK_LineWidth(SK_Line *_Nonnull, M_Real);
extern DECLSPEC void SK_LineColor(SK_Line *_Nonnull, M_Color);
extern DECLSPEC int SK_LineSharedEndpoint(SK_Line *_Nonnull, SK_Line *_Nonnull, M_Vector3 *_Nonnull, M_Vector3 *_Nonnull, M_Vector3 *_Nonnull);
extern DECLSPEC M_Real SK_LineLineAngleCCW(SK_Line *_Nonnull, SK_Line *_Nonnull);
__END_DECLS
/* Close generated block */
