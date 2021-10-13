/*	Public domain	*/

typedef struct sg_octnode {
	M_Vector3 min, max;	/* Extent of cube */
	M_Vector3 ctr;		/* Center point */
	M_Real halfWd;		/* Half width */
	Uint *polys;		/* Polygon names */
	Uint npolys;
	SG_Octnode *Q[8];	/* Subnodes */
} SG_Octnode;

typedef struct sg_octree {
	SG_Octnode *root;
} SG_Octree;

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC void SG_OctreeInit(SG_Octree *);
extern DECLSPEC void SG_OctreeBuild(SG *, SG_Octree *);
__END_DECLS
/* Close generated block */
