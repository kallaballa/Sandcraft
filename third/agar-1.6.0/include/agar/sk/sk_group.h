/*	Public domain	*/

typedef struct sk_group {
	struct sk_node _inherit;
	SK_Node *_Nullable *_Nullable nodes;	/* Nodes in group */
	Uint                         nNodes;
	Uint32 _pad;
	M_Color color;				/* Selection color */
} SK_Group;

#define SKGROUP(n) ((SK_Group *)(n))

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC SK_NodeOps skGroupOps;
extern DECLSPEC SK_Group *_Nonnull SK_GroupNew(void *_Nonnull);
extern DECLSPEC void SK_GroupInit(void *_Nonnull, Uint);
extern DECLSPEC int SK_GroupLoad(SK *_Nonnull, void *_Nonnull, AG_DataSource *_Nonnull);
extern DECLSPEC int SK_GroupSave(SK *_Nonnull, void *_Nonnull, AG_DataSource *_Nonnull);
extern DECLSPEC void SK_GroupEdit(void *_Nonnull, struct ag_widget *_Nonnull, struct sk_view *_Nonnull);
extern DECLSPEC void SK_GroupColor(SK_Group *_Nonnull, M_Color);
__END_DECLS
/* Close generated block */
