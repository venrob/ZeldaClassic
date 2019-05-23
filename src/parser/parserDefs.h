#ifndef _PARSERDEFS_H_
#define _PARSERDEFS_H_

//FUNCFLAG values, for `Function` and `ASTFuncDecl` objects.
#define FUNCFLAG_INLINE				0x01
#define FUNCFLAG_INVALID			0x02

//Option values. NOTE: Result of "lookupOption" must be '/10000.0' -V
#define OPT_OFF                     0
#define OPT_ON                      1
#define OPT_ERROR                   2
#define OPT_WARN                    3

#define OPTTYPE_QR                  0
#define OPTTYPE_CONFIG              1

#define MAX_INCLUDE_PATHS           5

#endif

