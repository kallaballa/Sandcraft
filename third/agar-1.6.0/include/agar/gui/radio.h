/*	Public domain	*/

#ifndef _AGAR_WIDGET_RADIO_H_
#define _AGAR_WIDGET_RADIO_H_

#include <agar/gui/widget.h>

#include <agar/gui/begin.h>

#ifndef AG_RADIO_TEXT_MAX
#define AG_RADIO_TEXT_MAX (AG_MODEL*2)
#endif

typedef enum ag_radio_type {
	AG_RADIO_VERT,                  /* Vertical disposition */
	AG_RADIO_HORIZ,                 /* Horizontal disposition */
	AG_RADIO_TYPE_LAST
} AG_RadioType;

typedef struct ag_radio_item {
	char text[AG_RADIO_TEXT_MAX];	/* Display text */
	int  surface;			/* Cached surface */
	AG_KeySym hotkey;		/* Associated key (or AG_KEY_NONE) */
} AG_RadioItem;

typedef struct ag_radio {
	struct ag_widget wid;           /* AG_Widget -> AG_Radio */
	AG_RadioType type;              /* Disposition */
	Uint flags;
#define AG_RADIO_HFILL	0x01
#define AG_RADIO_VFILL	0x02
#define AG_RADIO_EXPAND (AG_RADIO_HFILL | AG_RADIO_VFILL)

	AG_RadioItem *_Nullable items;  /* Array of radio items */
	int                    nItems;

	int hoverItem;        /* Mouse hover item index */
	int extent;           /* Width of widest (or Height of highest) label */
	int value;            /* Default "value" binding */
	int wReq, hReq;       /* Size requisition */
	int wPre, hPre;       /* Size hint */
	int lastKeyDown;      /* For key repeat */
	Uint32 _pad;
	AG_Timer moveTo;      /* Timer for keyboard motion */
} AG_Radio;

#define AGRADIO(obj)            ((AG_Radio *)(obj))
#define AGCRADIO(obj)           ((const AG_Radio *)(obj))
#define AG_RADIO_SELF()          AGRADIO( AG_OBJECT(0,"AG_Widget:AG_Radio:*") )
#define AG_RADIO_PTR(n)          AGRADIO( AG_OBJECT((n),"AG_Widget:AG_Radio:*") )
#define AG_RADIO_NAMED(n)        AGRADIO( AG_OBJECT_NAMED((n),"AG_Widget:AG_Radio:*") )
#define AG_CONST_RADIO_SELF()   AGCRADIO( AG_CONST_OBJECT(0,"AG_Widget:AG_Radio:*") )
#define AG_CONST_RADIO_PTR(n)   AGCRADIO( AG_CONST_OBJECT((n),"AG_Widget:AG_Radio:*") )
#define AG_CONST_RADIO_NAMED(n) AGCRADIO( AG_CONST_OBJECT_NAMED((n),"AG_Widget:AG_Radio:*") )

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC AG_WidgetClass agRadioClass;
extern DECLSPEC AG_Radio *_Nonnull AG_RadioNewInt(void *_Nullable, Uint, const char *_Nullable *_Nullable, int *_Nonnull);
extern DECLSPEC AG_Radio *_Nonnull AG_RadioNewUint(void *_Nullable, Uint, const char *_Nullable *_Nullable, Uint *_Nonnull);
extern DECLSPEC AG_Radio *_Nonnull AG_RadioNew(void *_Nullable, Uint, const char *_Nullable *_Nullable);
extern DECLSPEC AG_Radio *_Nonnull AG_RadioNewFn(void *_Nullable, Uint, const char *_Nullable *_Nullable, _Nonnull AG_EventFn, const char *_Nullable, ...);
extern DECLSPEC void AG_RadioSetDisposition(AG_Radio *_Nonnull, AG_RadioType);
extern DECLSPEC void AG_RadioItemsFromArray(AG_Radio *_Nonnull, const char *_Nonnull *_Nullable);
extern DECLSPEC int AG_RadioAddItemS(AG_Radio *_Nonnull, const char *_Nonnull);
extern DECLSPEC int AG_RadioAddItem(AG_Radio *_Nonnull, const char *_Nonnull, ...) FORMAT_ATTRIBUTE(printf,2,3);
extern DECLSPEC int AG_RadioAddItemHKS(AG_Radio *_Nonnull, AG_KeySym, const char *_Nonnull);
extern DECLSPEC int AG_RadioAddItemHK(AG_Radio *_Nonnull, AG_KeySym, const char *_Nonnull, ...) FORMAT_ATTRIBUTE(printf,3,4);
extern DECLSPEC void AG_RadioClearItems(AG_Radio *_Nonnull);
extern DECLSPEC void AG_RadioSizeHint(AG_Radio *_Nonnull, int, const char *);
__END_DECLS
/* Close generated block */

#include <agar/gui/close.h>
#endif /* _AGAR_WIDGET_RADIO_H_ */
