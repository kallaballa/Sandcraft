/*	Public domain	*/

#ifndef _AGAR_CORE_DIR_H_
#define _AGAR_CORE_DIR_H_

#include <agar/config/ag_serialization.h>
#ifdef AG_SERIALIZATION

#include <agar/core/begin.h>

typedef struct ag_dir {
	void *_Nullable           dirp;	    /* Internal handle */
	char *_Nullable *_Nonnull ents;     /* Entries in UTF-8 */
	Uint                     nents;
	int                       fd;	    /* Open file descriptor (or -1) */
} AG_Dir;

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC int AG_MkDir(const char *_Nonnull);
extern DECLSPEC int AG_RmDir(const char *_Nonnull);
extern DECLSPEC int AG_ChDir(const char *_Nonnull);
extern DECLSPEC AG_Dir *_Nullable AG_OpenDir(const char *_Nonnull);
extern DECLSPEC void AG_CloseDir(AG_Dir *_Nonnull);
extern DECLSPEC int AG_MkPath(const char *_Nonnull);
extern DECLSPEC int AG_GetCWD(char *_Nonnull, AG_Size);
__END_DECLS
/* Close generated block */

#include <agar/core/close.h>
#endif /* AG_SERIALIZATION */
#endif /* _AGAR_CORE_DIR_H_ */
