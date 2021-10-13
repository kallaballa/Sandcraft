/*	Public domain	*/

#ifndef _AGAR_MICRO_GUI_H_
#define _AGAR_MICRO_GUI_H_

#include <agar/micro/begin.h>

#define MA_ZOOM_MIN 0
#define MA_ZOOM_MAX 0
#define MA_ZOOM_1_1 0			/* Starts at 100% */
#ifndef MA_ZOOM_DEFAULT
#define MA_ZOOM_DEFAULT MA_ZOOM_1_1
#endif

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC Uint8 maGUI, maRenderingContext;
extern DECLSPEC Uint8 maKbdDelay_2;
extern DECLSPEC Uint8 maKbdRepeat;
extern DECLSPEC Uint8 maMouseDblclickDelay, maPageIncrement;
extern DECLSPEC Sint8 MA_InitGraphics(const char *_Nullable);
extern DECLSPEC void MA_DestroyGraphics(void);
extern DECLSPEC void MA_InitGUI(void);
extern DECLSPEC void MA_DestroyGUI(void);
extern DECLSPEC Sint8 MA_InitGUIGlobals(void);
extern DECLSPEC void MA_DestroyGUIGlobals(void);
__END_DECLS
/* Close generated block */

#include <agar/micro/close.h>
#endif /* _AGAR_MICRO_GUI_H_ */
