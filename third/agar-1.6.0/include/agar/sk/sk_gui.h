/*	Public domain	*/

#ifndef _AGAR_SK_GUI_H_
#define _AGAR_SK_GUI_H_

#include <agar/gui/gui.h>
#include <agar/gui/widget.h>
#include <agar/gui/window.h>
#include <agar/gui/text.h>
#include <agar/gui/icons.h>
#include <agar/gui/primitive.h>
#include <agar/gui/load_surface.h>

#include <agar/gui/button.h>
#include <agar/gui/file_dlg.h>
#include <agar/gui/font_selector.h>
#include <agar/gui/graph.h>
#include <agar/gui/hsvpal.h>
#include <agar/gui/menu.h>
#include <agar/gui/mfspinbutton.h>
#include <agar/gui/mspinbutton.h>
#include <agar/gui/notebook.h>
#include <agar/gui/numerical.h>
#include <agar/gui/pane.h>
#include <agar/gui/separator.h>
#include <agar/gui/table.h>
#include <agar/gui/units.h>

#include <agar/math/m.h>
#include <agar/math/m_gui.h>

#include <agar/sg/icons.h>

#include <agar/sk/sk_view.h>

#include <agar/sk/begin.h>
/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC AG_Object skVfsRoot; 
extern DECLSPEC void SK_InitGUI(void);
extern DECLSPEC void SK_DestroyGUI(void);
extern DECLSPEC void SK_FileMenu(AG_MenuItem *, void *);
extern DECLSPEC void SK_EditMenu(AG_MenuItem *, void *);
extern DECLSPEC AG_Window *SK_GUI_OpenObject(void *);
extern DECLSPEC void SK_GUI_NewObject(AG_Event *);
extern DECLSPEC void SK_GUI_LoadObject(AG_Event *);
extern DECLSPEC void SK_GUI_ImportObjectDlg(AG_Event *);
extern DECLSPEC void SK_GUI_OpenDlg(AG_Event *);
extern DECLSPEC void SK_GUI_SaveAsDlg(AG_Event *);
extern DECLSPEC void SK_GUI_Save(AG_Event *);
extern DECLSPEC void SK_GUI_Quit(AG_Event *);
extern DECLSPEC void SK_GUI_Undo(AG_Event *);
extern DECLSPEC void SK_GUI_Redo(AG_Event *);
extern DECLSPEC void SK_GUI_EditPreferences(AG_Event *);
extern DECLSPEC void SK_GUI_SelectFontDlg(AG_Event *);
__END_DECLS
/* Close generated block */
#include <agar/sk/close.h>

#endif /* _AGAR_SK_GUI_H_ */
