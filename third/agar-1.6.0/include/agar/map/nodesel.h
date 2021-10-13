/*	Public domain	*/

#ifndef _AGAR_MAP_NODESEL_H_
#define _AGAR_MAP_NODESEL_H_
#include <agar/map/begin.h>

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC void MAP_NodeselBegin(MAP_View *_Nonnull);
extern DECLSPEC void MAP_NodeselEnd(MAP_View *_Nonnull);
extern DECLSPEC void MAP_NodeselBeginMove(MAP_View *_Nonnull);
extern DECLSPEC void MAP_NodeselUpdateMove(MAP_View *_Nonnull, int,int);
extern DECLSPEC void MAP_NodeselEndMove(MAP_View *_Nonnull);
extern DECLSPEC int MAP_NodeselCopy(MAP_Tool *_Nonnull, AG_KeySym, int, void *_Nullable);
extern DECLSPEC int MAP_NodeselPaste(MAP_Tool *_Nonnull, AG_KeySym, int, void *_Nullable);
extern DECLSPEC int MAP_NodeselCut(MAP_Tool *_Nonnull, AG_KeySym, int, void *_Nullable);
extern DECLSPEC int MAP_NodeselKill(MAP_Tool *_Nonnull, AG_KeySym, int, void *_Nullable);
__END_DECLS
/* Close generated block */

#include <agar/map/close.h>
#endif /* _AGAR_MAP_NODESEL_H_ */
