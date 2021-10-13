/*	Public domain	*/

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC void M_PolygonInit(M_Polygon *_Nonnull);
extern DECLSPEC void M_PolygonFree(M_Polygon *_Nonnull);
extern DECLSPEC M_Polygon M_PolygonFromPts(Uint, const M_Vector2 *_Nonnull);
extern DECLSPEC M_Polygon M_PolygonFromLines(Uint, const M_Line2 *_Nonnull);
extern DECLSPEC M_Polygon M_PolygonFromPointSet2(const M_PointSet2 *_Nonnull);
extern DECLSPEC M_Polygon M_PolygonFromPointSet2i(const M_PointSet2i *_Nonnull);
extern DECLSPEC M_PointSet2 M_PolygonToPointSet2(const M_Polygon *_Nonnull);
extern DECLSPEC M_PointSet2i M_PolygonToPointSet2i(const M_Polygon *_Nonnull, M_Real,M_Real);
extern DECLSPEC M_Polygon M_PolygonRead(AG_DataSource *_Nonnull);
extern DECLSPEC void M_PolygonWrite(AG_DataSource *_Nonnull, const M_Polygon *_Nonnull);
extern DECLSPEC int M_PolygonCopy(M_Polygon *_Nonnull, const M_Polygon *_Nonnull);
extern DECLSPEC void M_PolygonScale(M_Polygon *_Nonnull, M_Real,M_Real);
extern DECLSPEC void M_PolygonOffset(M_Polygon *_Nonnull, M_Real,M_Real);
extern DECLSPEC int M_PolygonAddLine(M_Polygon *_Nonnull, M_Line2);
extern DECLSPEC int M_PolygonAddVertex(M_Polygon *_Nonnull, M_Vector2);
extern DECLSPEC int M_PolygonDelVertex(M_Polygon *_Nonnull, int);
extern DECLSPEC int M_PointInPolygon(const M_Polygon *_Nonnull, M_Vector2);
extern DECLSPEC int M_PolygonIsConvex(const M_Polygon *_Nonnull);
__END_DECLS
/* Close generated block */
