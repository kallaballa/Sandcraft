/*	Public domain	*/

typedef struct sg_voxel {
	struct sg_node _inherit;		/* SG_Node -> SG_Voxel */
	int w, h, d;
	Uint32 _pad1;
	M_Real *_Nullable *_Nonnull *_Nonnull map;	/* Array of cells */
	Uint8 _pad2[8];
} SG_Voxel;

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC SG_NodeClass sgVoxelClass;
extern DECLSPEC SG_Voxel *_Nonnull SG_VoxelNew(void *_Nullable, const char *_Nullable);
extern DECLSPEC void SG_VoxelAlloc3(SG_Voxel *_Nonnull, Uint,Uint,Uint);
extern DECLSPEC void SG_VoxelReset(SG_Voxel *_Nonnull, M_Real);
extern DECLSPEC int SG_VoxelSet3(SG_Voxel *_Nonnull, int,int,int, M_Real);
__END_DECLS
/* Close generated block */
