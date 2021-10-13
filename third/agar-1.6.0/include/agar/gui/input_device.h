/*	Public domain	*/

#ifndef _AGAR_GUI_INPUT_DEVICE_H_
#define _AGAR_GUI_INPUT_DEVICE_H_
#include <agar/gui/begin.h>

typedef struct ag_input_device {
	struct ag_object _inherit;
	void *_Nullable drv;	/* Associated graphics driver */
	char *_Nullable desc;	/* User description */
	Uint flags;
	Uint32 _pad;
} AG_InputDevice;

#define AGINPUTDEV(obj) ((AG_InputDevice *)(obj))

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC AG_ObjectClass agInputDeviceClass;
extern DECLSPEC AG_Object agInputDevices; 
__END_DECLS
/* Close generated block */

#include <agar/gui/close.h>
#endif /* _AGAR_GUI_INPUT_DEVICE_H_ */
