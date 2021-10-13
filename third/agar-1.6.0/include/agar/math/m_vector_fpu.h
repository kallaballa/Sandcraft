/*
 * Public domain.
 * Operations on vectors in R^n using standard FPU instructions.
 */
/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC const M_VectorOps mVecOps_FPU;
extern DECLSPEC M_Vector *_Nonnull M_ReadVector_FPU(AG_DataSource *_Nonnull);
extern DECLSPEC void M_WriteVector_FPU(AG_DataSource *_Nonnull, const M_Vector *_Nonnull);
extern DECLSPEC M_Vector *_Nonnull M_VectorFromReals_FPU(Uint, const M_Real *_Nonnull);
extern DECLSPEC M_Vector *_Nonnull M_VectorFromFloats_FPU(Uint, const float *_Nonnull);
extern DECLSPEC M_Vector *_Nonnull M_VectorFromDoubles_FPU(Uint, const double *_Nonnull);
__END_DECLS
/* Close generated block */
