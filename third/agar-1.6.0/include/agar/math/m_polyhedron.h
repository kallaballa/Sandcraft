/*	Public domain	*/

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC void M_PolyhedronInit(M_Polyhedron *_Nonnull);
extern DECLSPEC void M_PolyhedronFree(M_Polyhedron *_Nonnull);
extern DECLSPEC int M_PolyhedronRead(AG_DataSource *_Nonnull, M_Polyhedron *_Nonnull);
extern DECLSPEC void M_PolyhedronWrite(AG_DataSource *_Nonnull, const M_Polyhedron *_Nonnull);
extern DECLSPEC Uint M_PolyhedronAddVertex(M_Polyhedron *_Nonnull, M_Vector3);
extern DECLSPEC void M_PolyhedronDelVertex(M_Polyhedron *_Nonnull, Uint);
extern DECLSPEC Uint M_PolyhedronAddEdge(M_Polyhedron *_Nonnull, int, int);
extern DECLSPEC void M_PolyhedronDelEdge(M_Polyhedron *_Nonnull, Uint);
extern DECLSPEC Uint M_PolyhedronAddFacet(M_Polyhedron *_Nonnull, Uint, const Uint *_Nonnull);
extern DECLSPEC void M_PolyhedronDelFacet(M_Polyhedron *_Nonnull, Uint);
__END_DECLS
/* Close generated block */
