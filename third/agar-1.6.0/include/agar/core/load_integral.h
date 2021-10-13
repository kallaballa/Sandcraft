/*	Public domain	*/
/*
 * Serialization of integers.
 */

#ifndef	_AGAR_CORE_LOAD_INTEGRAL_H_
#define	_AGAR_CORE_LOAD_INTEGRAL_H_
#include <agar/core/begin.h>

/* Begin generated block */
__BEGIN_DECLS
/*
 * Inlinables
 */
extern DECLSPEC Uint8 ag_read_uint8(AG_DataSource *_Nonnull);
extern DECLSPEC void ag_write_uint8(AG_DataSource *_Nonnull, Uint8);
extern DECLSPEC void ag_write_uint8_at(AG_DataSource *_Nonnull, Uint8, AG_Offset);
extern DECLSPEC Sint8 ag_read_sint8(AG_DataSource *_Nonnull);
extern DECLSPEC void ag_write_sint8(AG_DataSource *_Nonnull, Sint8);
extern DECLSPEC void ag_write_sint8_at(AG_DataSource *_Nonnull, Sint8, AG_Offset);
extern DECLSPEC Uint16 ag_read_uint16(AG_DataSource *_Nonnull);
extern DECLSPEC void ag_write_uint16(AG_DataSource *_Nonnull, Uint16);
extern DECLSPEC void ag_write_uint16_at(AG_DataSource *_Nonnull, Uint16, AG_Offset);
extern DECLSPEC Sint16 ag_read_sint16(AG_DataSource *_Nonnull);
extern DECLSPEC void ag_write_sint16(AG_DataSource *_Nonnull, Sint16);
extern DECLSPEC void ag_write_sint16_at(AG_DataSource *_Nonnull, Sint16, AG_Offset);
extern DECLSPEC Uint32 ag_read_uint32(AG_DataSource *_Nonnull);
extern DECLSPEC void ag_write_uint32(AG_DataSource *_Nonnull, Uint32);
extern DECLSPEC void ag_write_uint32_at(AG_DataSource *_Nonnull, Uint32, AG_Offset);
extern DECLSPEC Sint32 ag_read_sint32(AG_DataSource *_Nonnull);
extern DECLSPEC void ag_write_sint32(AG_DataSource *_Nonnull, Sint32);
extern DECLSPEC void ag_write_sint32_at(AG_DataSource *_Nonnull, Sint32, AG_Offset);
#ifdef AG_HAVE_64BIT
extern DECLSPEC Uint64 ag_read_uint64(AG_DataSource *_Nonnull);
extern DECLSPEC void ag_write_uint64(AG_DataSource *_Nonnull, Uint64);
extern DECLSPEC void ag_write_uint64_at(AG_DataSource *_Nonnull, Uint64, AG_Offset);
extern DECLSPEC Sint64 ag_read_sint64(AG_DataSource *_Nonnull);
extern DECLSPEC void ag_write_sint64(AG_DataSource *_Nonnull, Sint64);
extern DECLSPEC void ag_write_sint64_at(AG_DataSource *_Nonnull, Sint64, AG_Offset);
#endif
#ifdef AG_INLINE_IO
# define AG_INLINE_HEADER
# include <agar/core/inline_load_integral.h>
#else
# define AG_ReadUint8(ds) ag_read_uint8(ds)
# define AG_WriteUint8(ds,i) ag_write_uint8((ds),(i))
# define AG_WriteUint8At(ds,i,pos) ag_write_uint8_at((ds),(i),(pos))
# define AG_ReadSint8(ds) ag_read_sint8(ds)
# define AG_WriteSint8(ds,i) ag_write_sint8((ds),(i))
# define AG_WriteSint8At(ds,i,pos) ag_write_sint8_at((ds),(i),(pos))
# define AG_ReadUint16(ds) ag_read_uint16(ds)
# define AG_WriteUint16(ds,i) ag_write_uint16((ds),(i))
# define AG_WriteUint16At(ds,i,pos) ag_write_uint16_at((ds),(i),(pos))
# define AG_ReadSint16(ds) ag_read_sint16(ds)
# define AG_WriteSint16(ds,i) ag_write_sint16((ds),(i))
# define AG_WriteSint16At(ds,i,pos) ag_write_sint16_at((ds),(i),(pos))
# define AG_ReadUint32(ds) ag_read_uint32(ds)
# define AG_WriteUint32(ds,i) ag_write_uint32((ds),(i))
# define AG_WriteUint32At(ds,i,pos) ag_write_uint32_at((ds),(i),(pos))
# define AG_ReadSint32(ds) ag_read_sint32(ds)
# define AG_WriteSint32(ds,i) ag_write_sint32((ds),(i))
# define AG_WriteSint32At(ds,i,pos) ag_write_sint32_at((ds),(i),(pos))
# define AG_ReadUint64(ds) ag_read_uint64(ds)
# define AG_WriteUint64(ds,i) ag_write_uint64((ds),(i))
# define AG_WriteUint64At(ds,i,pos) ag_write_uint64_at((ds),(i),(pos))
# define AG_ReadSint64(ds) ag_read_sint64(ds)
# define AG_WriteSint64(ds,i) ag_write_sint64((ds),(i))
# define AG_WriteSint64At(ds,i,pos) ag_write_sint64_at((ds),(i),(pos))
#endif
__END_DECLS
/* Close generated block */
#include <agar/core/close.h>
#endif /* _AGAR_CORE_LOAD_INTEGRAL_H_ */
