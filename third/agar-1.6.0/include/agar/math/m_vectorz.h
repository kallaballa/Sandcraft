/*	Public domain	*/

typedef struct m_vectorz {
	Uint n;
	Uint32 _pad;
	int *_Nonnull v;
} M_VectorZ;

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC M_VectorZ *_Nonnull M_VectorNewZ(Uint);
extern DECLSPEC void M_VectorSetZ(M_VectorZ *_Nonnull, int);
extern DECLSPEC void M_VectorCopyZ(const M_VectorZ *_Nonnull, M_VectorZ *_Nonnull);
extern DECLSPEC void M_VectorFreeZ(M_VectorZ *_Nonnull);
extern DECLSPEC void M_VectorAddZv(M_VectorZ *_Nonnull, const M_VectorZ *_Nonnull);
extern DECLSPEC void M_VectorSubZv(M_VectorZ *_Nonnull, const M_VectorZ *_Nonnull);
extern DECLSPEC void M_VectorScaleZv(M_VectorZ *_Nonnull, M_Real);
extern DECLSPEC void M_VectorResizeV(M_VectorZ *_Nonnull, Uint);
extern DECLSPEC void M_VectorPrintZ(const M_VectorZ *_Nonnull);
__END_DECLS
/* Close generated block */
