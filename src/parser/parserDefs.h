#ifndef _PARSERDEFS_H_
#define _PARSERDEFS_H_

//Option values. NOTE: Result of "lookupOption" must be '/10000.0' -V
#define OPT_OFF                     0
#define OPT_ON                      1
#define OPT_ERROR                   2
#define OPT_WARN                    3

#define OPTTYPE_QR                  0
#define OPTTYPE_CONFIG              1

#define MAX_INCLUDE_PATHS           5

enum regSize
{
	REGSIZE_BOOL,
	REGSIZE_CHAR,
	REGSIZE_INT
};

inline long wrap_unsigned(long num, int bits)
{
	const long inc = 1<<bits;
    while(num<0)num+=inc;
    return num%inc;
}

inline long wrap_signed(long num, int bits)
{
	const long inc = 1<<bits;
    const long min = -inc / 2, max = (inc/2) - 1;
    while(num>max)num-=inc;
    while(num<min)num+=inc;
}

#endif

