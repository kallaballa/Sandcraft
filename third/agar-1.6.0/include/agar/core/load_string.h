/*	Public domain	*/

#ifndef	_AGAR_CORE_LOAD_STRING_H_
#define	_AGAR_CORE_LOAD_STRING_H_

#ifndef AG_LOAD_STRING_MAX
#define AG_LOAD_STRING_MAX 0xfffe
#endif

#include <agar/core/begin.h>

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC char *_Nullable AG_ReadString(AG_DataSource *);
extern DECLSPEC char *_Nullable AG_ReadStringLen(AG_DataSource *_Nonnull, AG_Size);
extern DECLSPEC char *_Nullable AG_ReadStringPadded(AG_DataSource *_Nonnull, AG_Size);
extern DECLSPEC char *_Nullable AG_ReadNulString(AG_DataSource *_Nonnull);
extern DECLSPEC char *_Nullable AG_ReadNulStringLen(AG_DataSource *_Nonnull, AG_Size);
extern DECLSPEC void AG_WriteString(AG_DataSource *_Nonnull, const char *_Nullable);
extern DECLSPEC void AG_WriteStringPadded(AG_DataSource *_Nonnull, const char *_Nullable, AG_Size);
extern DECLSPEC AG_Size AG_CopyString(char *_Nonnull, AG_DataSource *_Nonnull, AG_Size);
extern DECLSPEC AG_Size AG_CopyStringPadded(char *_Nonnull, AG_DataSource *_Nonnull, AG_Size);
extern DECLSPEC AG_Size AG_CopyNulString(char *_Nonnull, AG_DataSource *_Nonnull, AG_Size);
extern DECLSPEC void AG_SkipString(AG_DataSource *_Nonnull);
extern DECLSPEC void AG_SkipStringPadded(AG_DataSource *_Nonnull);
__END_DECLS
/* Close generated block */

#include <agar/core/close.h>
#endif /* _AGAR_CORE_LOAD_STRING_H_ */
