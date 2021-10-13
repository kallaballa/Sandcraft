/*	Public domain	*/

#ifndef	_AGAR_CORE_VSNPRINTF_H_
#define	_AGAR_CORE_VSNPRINTF_H_

#include <agar/config/_mk_have_sys_types_h.h>
#ifdef _MK_HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#include <stdarg.h>

#include <agar/core/begin.h>
/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC int AG_TryVsnprintf(char *_Nonnull, AG_Size, const char *_Nonnull, va_list);
extern DECLSPEC void AG_Vsnprintf(char *_Nonnull, AG_Size, const char *_Nonnull, va_list);
#if defined(_AGAR_INTERNAL) || defined(_USE_AGAR_STD)
# define Vsnprintf(s,size,fmt,ap) AG_Vsnprintf((s),(size),(fmt),(ap))
# define TryVsnprintf(s,size,fmt,ap) AG_TryVsnprintf((s),(size),(fmt),(ap))
#endif
__END_DECLS
/* Close generated block */
#include <agar/core/close.h>
#endif /* _AGAR_CORE_VSNPRINTF_H_ */
