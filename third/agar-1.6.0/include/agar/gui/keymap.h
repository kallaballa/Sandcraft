/*	Public domain	*/

#ifndef _AGAR_WIDGET_KEYMAP_H_
#define _AGAR_WIDGET_KEYMAP_H_
#include <agar/gui/begin.h>

struct ag_editable;
struct ag_editable_buffer;

struct ag_keycode {
	AG_KeySym key;			/* Match keysym */
	Uint      modKeys;		/* Match set of modifier keys */
	int (*_Nonnull func)(struct ag_editable *_Nonnull,
	                     struct ag_editable_buffer *_Nonnull,
	                     AG_KeySym, Uint, AG_Char);
	const char *_Nonnull flags;
};

struct ag_key_composition {
	AG_Char comp;		/* This first key */
	AG_Char key;		/* And this second key */
	AG_Char res;		/* Combines into this native char */
};

struct ag_key_mapping {
	AG_KeySym key;		/* This key */
	Uint modmask;		/* With this modifier mask */
	AG_Char ch;		/* Maps to this native char */ 
};

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC const struct ag_keycode agKeymap[];
#ifdef AG_UNICODE
extern DECLSPEC const struct ag_key_mapping agKeymapLATIN1[];
extern DECLSPEC const struct ag_key_composition agCompositionMap[];
extern DECLSPEC const int agCompositionMapSize;
extern DECLSPEC int AG_KeyInputCompose(struct ag_editable *_Nonnull, AG_Char, AG_Char *_Nonnull);
#endif 
__END_DECLS
/* Close generated block */

#include <agar/gui/close.h>
#endif	/* _AGAR_WIDGET_KEYMAP_H_ */
