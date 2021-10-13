/*	Public domain	*/

#ifndef _AGAR_CORE_CONFIG_H_
#define _AGAR_CORE_CONFIG_H_

#include <agar/config/ag_serialization.h>
#ifdef AG_SERIALIZATION

#include <agar/core/begin.h>

typedef enum ag_config_path_group {
	AG_CONFIG_PATH_DATA,	/* Objects and data from */
	AG_CONFIG_PATH_FONTS,	/* Font files */
	AG_CONFIG_PATH_TEMP,	/* Temporary files */
	AG_CONFIG_PATH_LAST
} AG_ConfigPathGroup;

typedef struct ag_config_path {
	char *_Nonnull s;			/* Path to directory */
	AG_TAILQ_ENTRY(ag_config_path) paths;
} AG_ConfigPath;

typedef AG_TAILQ_HEAD(ag_config_pathq, ag_config_path) AG_ConfigPathQ;

typedef struct ag_config {
	struct ag_object _inherit;              /* AG_Object(3) -> AG_Config */
	AG_ConfigPathQ paths[AG_CONFIG_PATH_LAST];  /* Configured load paths */
} AG_Config;

#define AGCONFIG(obj)            ((AG_Config *)(obj))
#define AGCCONFIG(obj)           ((const AG_Config *)(obj))
#define AG_CONFIG_SELF()          AGCONFIG( AG_OBJECT(0,"AG_Config:*") )
#define AG_CONFIG_PTR(n)          AGCONFIG( AG_OBJECT((n),"AG_Config:*") )
#define AG_CONFIG_NAMED(n)        AGCONFIG( AG_OBJECT_NAMED((n),"AG_Config:*") )
#define AG_CONST_CONFIG_SELF()   AGCCONFIG( AG_CONST_OBJECT(0,"AG_Config:*") )
#define AG_CONST_CONFIG_PTR(n)   AGCCONFIG( AG_CONST_OBJECT((n),"AG_Config:*") )
#define AG_CONST_CONFIG_NAMED(n) AGCCONFIG( AG_CONST_OBJECT_NAMED((n),"AG_Config:*") )

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC AG_Config *_Nullable agConfig;
extern DECLSPEC AG_ObjectClass agConfigClass;
extern DECLSPEC const char *agConfigPathGroupNames[];
extern DECLSPEC int AG_ConfigInit(AG_Config *_Nonnull, Uint);
extern DECLSPEC int AG_CreateDataDir(void);
extern DECLSPEC int AG_ConfigSave(void);
extern DECLSPEC int AG_ConfigLoad(void);
extern DECLSPEC void AG_ConfigClearPaths(AG_Config *_Nonnull);
extern DECLSPEC AG_Config *_Nullable AG_ConfigObject(void);
extern DECLSPEC AG_Size AG_ConfigGetPath(AG_ConfigPathGroup, int, char *_Nonnull, AG_Size);
extern DECLSPEC int AG_ConfigSetPath(AG_ConfigPathGroup, int, const char *_Nonnull, ...);
extern DECLSPEC int AG_ConfigSetPathS(AG_ConfigPathGroup, int, const char *_Nonnull);
extern DECLSPEC int AG_ConfigFind(AG_ConfigPathGroup, const char *_Nonnull, char *_Nonnull, AG_Size);
extern DECLSPEC void AG_ConfigAddPathS(AG_ConfigPathGroup, const char *_Nonnull);
extern DECLSPEC void AG_ConfigAddPath(AG_ConfigPathGroup, const char *_Nonnull, ...) FORMAT_ATTRIBUTE(printf,2,3);
extern DECLSPEC void AG_ConfigDelPathS(AG_ConfigPathGroup, const char *_Nonnull);
extern DECLSPEC void AG_ConfigDelPath(AG_ConfigPathGroup, const char *_Nonnull, ...) FORMAT_ATTRIBUTE(printf,2,3);
#ifdef AG_LEGACY
extern DECLSPEC int AG_ConfigFile(const char *_Nonnull, const char *_Nonnull, const char *_Nullable, char *_Nonnull, AG_Size) DEPRECATED_ATTRIBUTE;
#endif
__END_DECLS
/* Close generated block */

#include <agar/core/close.h>
#endif /* AG_SERIALIZATION */
#endif /* _AGAR_CORE_CONFIG_H_ */
