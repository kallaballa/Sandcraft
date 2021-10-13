/*	Public domain	*/

#ifndef _AGAR_GUI_GUI_H_
#define _AGAR_GUI_GUI_H_

#include <agar/config/have_sdl.h>
#include <agar/gui/begin.h>

#define AG_ZOOM_MIN 0
#define AG_ZOOM_MAX 20
#define AG_ZOOM_1_1 8		/* 12.5% to 100% (in 8 increments) */
#ifndef AG_ZOOM_DEFAULT
#define AG_ZOOM_DEFAULT AG_ZOOM_1_1
#endif

/* Flags for AG_InitVideoSDL() */
#define AG_VIDEO_HWSURFACE     0x0001
#define AG_VIDEO_ASYNCBLIT     0x0002
#define AG_VIDEO_ANYFORMAT     0x0004
#define AG_VIDEO_HWPALETTE     0x0008
#define AG_VIDEO_DOUBLEBUF     0x0010
#define AG_VIDEO_FULLSCREEN    0x0020
#define AG_VIDEO_RESIZABLE     0x0040
#define AG_VIDEO_NOFRAME       0x0080
#define AG_VIDEO_BGPOPUPMENU   0x0100
#define AG_VIDEO_OPENGL	       0x0200
#define AG_VIDEO_OPENGL_OR_SDL 0x0400
#define AG_VIDEO_NOBGCLEAR     0x0800
#define AG_VIDEO_OVERLAY       0x1000
#define AG_VIDEO_SDL           0x2000

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC int agGUI, agRenderingContext, agStereo, agXsync, agClipboardIntegration;
extern DECLSPEC int agKbdDelay, agKbdRepeat;
extern DECLSPEC int agMouseDblclickDelay, agMouseSpinDelay, agMouseSpinIval, agMouseScrollIval, agScrollButtonIval, agPageIncrement, agAutocompleteDelay, agAutocompleteRate, agScreenshotQuality;
extern DECLSPEC int agTextComposition, agTextTabWidth, agTextBlinkRate;
extern DECLSPEC int agGLdebugOutput, agGLuseNPOT;
extern DECLSPEC double agZoomValues[AG_ZOOM_MAX];
#ifdef AG_EVENT_LOOP
extern DECLSPEC void AG_QuitGUI(void);
#endif
extern DECLSPEC int AG_InitGraphics(const char *_Nullable);
extern DECLSPEC void AG_DestroyGraphics(void);
extern DECLSPEC void AG_ZoomIn(void);
extern DECLSPEC void AG_ZoomOut(void);
extern DECLSPEC void AG_ZoomReset(void);
extern DECLSPEC int AG_InitGUI(Uint);
extern DECLSPEC void AG_DestroyGUI(void);
extern DECLSPEC int AG_InitGUIGlobals(void);
extern DECLSPEC void AG_DestroyGUIGlobals(void);
#ifdef HAVE_SDL
extern DECLSPEC int AG_InitVideoSDL(void *_Nonnull, Uint);
extern DECLSPEC int AG_SetVideoSurfaceSDL(void *_Nonnull);
#endif
#ifdef AG_WIDGETS
extern DECLSPEC void AG_About(struct ag_event *_Nullable);
extern DECLSPEC struct ag_window *_Nullable AG_StyleEditor(struct ag_window *_Nonnull);
extern DECLSPEC void AG_StyleEditorDetachTarget(void);
extern DECLSPEC void AG_StyleEditorDetachWindow(void);
# ifdef AG_DEBUG
extern DECLSPEC struct ag_window *_Nullable AG_GuiDebugger(struct ag_window *_Nonnull);
extern DECLSPEC void AG_GuiDebuggerDetachTarget(void);
extern DECLSPEC void AG_GuiDebuggerDetachWindow(void);
# endif
extern DECLSPEC void AG_DEV_ConfigShow(void);
extern DECLSPEC void *_Nullable AG_DEV_ObjectEdit(void *_Nonnull);
# ifdef AG_TIMERS
extern DECLSPEC struct ag_window *_Nullable AG_DEV_Browser(void *_Nonnull);
extern DECLSPEC struct ag_window *_Nullable AG_DEV_ClassInfo(void);
extern DECLSPEC struct ag_window *_Nullable AG_DEV_FontInfo(void);
# ifdef AG_ENABLE_STRING
extern DECLSPEC struct ag_window *_Nullable AG_DEV_TimerInspector(void);
# endif
# endif
# ifdef AG_UNICODE
extern DECLSPEC struct ag_window *_Nullable AG_DEV_UnicodeBrowser(void);
# endif
extern DECLSPEC struct ag_window *_Nullable AG_DEV_CPUInfo(void);
#endif 
#ifdef AG_LEGACY
extern DECLSPEC int AG_InitVideo(int,int, int, Uint) DEPRECATED_ATTRIBUTE;
extern DECLSPEC void AG_DestroyVideo(void) DEPRECATED_ATTRIBUTE;
#endif
__END_DECLS
/* Close generated block */

#include <agar/gui/close.h>
#endif /* _AGAR_GUI_GUI_H_ */
