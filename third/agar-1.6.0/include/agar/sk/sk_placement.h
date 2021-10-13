/*	Public domain	*/

typedef struct sk_constraint_pair_fn {
	enum sk_constraint_type ctType;
	Uint flags;
	const char *type1, *type2;
	int (*fn)(SK_Constraint *, void *, void *);
} SK_ConstraintPairFn;

typedef struct sk_constraint_ring_fn {
	enum sk_constraint_type ctType1;
	enum sk_constraint_type ctType2;
	const char *type1;
	const char *type2;
	const char *type3;
	int (*fn)(void *, SK_Constraint *, void *, SK_Constraint *, void *);
} SK_ConstraintRingFn;

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC const SK_ConstraintPairFn skConstraintPairFns[];
extern DECLSPEC const SK_ConstraintRingFn skConstraintRingFns[];
extern DECLSPEC const int skConstraintPairFnCount;
extern DECLSPEC const int skConstraintRingFnCount;
__END_DECLS
/* Close generated block */

