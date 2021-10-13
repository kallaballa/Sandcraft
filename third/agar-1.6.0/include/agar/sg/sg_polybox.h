/*	Public domain	*/

typedef struct sg_polybox {
	struct sg_object _inherit;	/* SG_Object -> SG_Polybox */
} SG_Polybox;

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC SG_NodeClass sgPolyboxClass;
extern DECLSPEC SG_Polybox *_Nonnull SG_PolyboxNew(void *_Nullable, const char *_Nullable);
__END_DECLS
/* Close generated block */
