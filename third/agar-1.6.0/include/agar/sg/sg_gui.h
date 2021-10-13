/*	Public domain	*/

#ifndef _AGAR_SG_SG_GUI_H_
#define _AGAR_SG_SG_GUI_H_

#include <agar/gui/gui.h>
#include <agar/gui/icons.h>
#include <agar/gui/surface.h>
#include <agar/gui/primitive.h>
#include <agar/gui/load_surface.h>

#include <agar/gui/checkbox.h>
#include <agar/gui/console.h>
#include <agar/gui/dir_dlg.h>
#include <agar/gui/file_dlg.h>
#include <agar/gui/font_selector.h>
#include <agar/gui/hsvpal.h>
#include <agar/gui/menu.h>
#include <agar/gui/notebook.h>
#include <agar/gui/numerical.h>
#include <agar/gui/objsel.h>
#include <agar/gui/pixmap.h>
#include <agar/gui/scrollview.h>
#include <agar/gui/slider.h>
#include <agar/gui/radio.h>
#include <agar/gui/table.h>
#include <agar/gui/separator.h>

#include <agar/sg/sg_view.h>
#include <agar/sg/sg_palette_view.h>
#include <agar/sg/icons.h>

#include <agar/sg/begin.h>

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC AG_Object sgVfsRoot; 
extern DECLSPEC void SG_InitGUI(void);
extern DECLSPEC void SG_DestroyGUI(void);
extern DECLSPEC void SG_FileMenu(AG_MenuItem *, void *, AG_Window *);
extern DECLSPEC void SG_EditMenu(AG_MenuItem *, void *, AG_Window *);
extern DECLSPEC void SG_ViewMenu(AG_MenuItem *, void *, AG_Window *, SG_View *);
extern DECLSPEC AG_Window *SG_GUI_OpenObject(void *);
extern DECLSPEC void SG_GUI_NewObject(AG_Event *);
extern DECLSPEC AG_Object *SG_GUI_LoadObject(AG_ObjectClass *, const char *);
extern DECLSPEC void SG_GUI_OpenDlg(AG_Event *);
extern DECLSPEC void SG_GUI_SaveAsDlg(AG_Event *);
extern DECLSPEC void SG_GUI_Save(AG_Event *);
extern DECLSPEC void SG_GUI_Quit(AG_Event *);
extern DECLSPEC void SG_GUI_Undo(AG_Event *);
extern DECLSPEC void SG_GUI_Redo(AG_Event *);
extern DECLSPEC void SG_GUI_EditPreferences(AG_Event *);
extern DECLSPEC void SG_GUI_SelectFontDlg(AG_Event *);
extern DECLSPEC void SG_GUI_CreateNewDlg(AG_Event *);
extern DECLSPEC void SG_GUI_PollNodes(AG_Event *);
extern DECLSPEC void SG_GUI_CreateNewView(AG_Event *);
extern DECLSPEC SG_Node *SG_GUI_CreateNode(SG *, AG_ObjectClass *);
extern DECLSPEC void SG_GUI_DeleteNode(SG_Node *, SG_View *);
extern DECLSPEC void SG_GUI_NodePopupMenu(AG_Event *);
extern DECLSPEC void SG_GUI_EditNode(SG_Node *, AG_Widget *, SG_View *);
__END_DECLS
/* Close generated block */
#include <agar/sg/close.h>

#endif /* _AGAR_SG_SG_GUI_H_ */
