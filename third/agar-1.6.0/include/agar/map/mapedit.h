/*	Public domain	*/

#include <agar/map/begin.h>

typedef struct map_editor {
	AG_Object obj;
	MAP copybuf;		/* Copy/paste buffer */
} MAP_Editor;

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC AG_ObjectClass mapEditorClass;
extern DECLSPEC AG_ObjectClass mapEditorPseudoClass;
extern DECLSPEC MAP_Editor mapEditor;
extern DECLSPEC void MAP_EditorInit(void);
extern DECLSPEC void MAP_EditorLoad(AG_DataSource *_Nonnull);
extern DECLSPEC void MAP_EditorSave(AG_DataSource *_Nonnull);
__END_DECLS
/* Close generated block */

#include <agar/map/close.h>
