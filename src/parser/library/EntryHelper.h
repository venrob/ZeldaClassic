// Meant to be included in an anonymous namespace to help with defining the
// Library::Entry table for library subclasses.

#ifndef ZSCRIPT_LIBRARY_ENTRY_HELPER
#define ZSCRIPT_LIBRARY_ENTRY_HELPER

// tSelf should be defined to the proper type, like below.

#define tAny ScriptParser::TYPE_UNTYPED
#define tVoid ScriptParser::TYPE_VOID
#define tFlt ScriptParser::TYPE_FLOAT
#define tBool ScriptParser::TYPE_BOOL

#define tItm ScriptParser::TYPE_ITEM
#define tItmC ScriptParser::TYPE_ITEMCLASS
#define tFfc ScriptParser::TYPE_FFC
#define tNpc ScriptParser::TYPE_NPC
#define tNpcC ScriptParser::TYPE_NPCDATA
#define tLW ScriptParser::TYPE_LWPN
#define tEW ScriptParser::TYPE_EWPN
#define tCmb ScriptParser::TYPE_COMBOS
#define tMap ScriptParser::TYPE_MAPDATA
#define tSpr ScriptParser::TYPE_SPRITEDATA
#define tShp ScriptParser::TYPE_SHOPDATA
#define tGfx ScriptParser::TYPE_GRAPHICS
#define tMsg ScriptParser::TYPE_ZMESSAGE
#define tDMap ScriptParser::TYPE_DMAPDATA

// Last Entry
#define ENTRY_END \
	{ "", -1, -1, -1, -1, { -1,  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } }

#ifdef tSelf
// Parameter Macros
#	define P0 \
	{ tSelf,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P1( A) \
	{ tSelf,    A, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P2( A,  B) \
	{ tSelf,    A,  B, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P3( A,  B,  C) \
	{ tSelf,    A,  B,  C, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P4( A,  B,  C,  D) \
	{ tSelf,    A,  B,  C,  D, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P5( A,  B,  C,  D,  E) \
	{ tSelf,    A,  B,  C,  D,  E, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P6( A,  B,  C,  D,  E,  F) \
	{ tSelf,    A,  B,  C,  D,  E,  F, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P7( A,  B,  C,  D,  E,  F,  G) \
	{ tSelf,    A,  B,  C,  D,  E,  F,  G, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P8( A,  B,  C,  D,  E,  F,  G,  H) \
	{ tSelf,    A,  B,  C,  D,  E,  F,  G,  H, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P9( A,  B,  C,  D,  E,  F,  G,  H,  I) \
	{ tSelf,    A,  B,  C,  D,  E,  F,  G,  H,  I, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P10(A,  B,  C,  D,  E,  F,  G,  H,  I,  J) \
	{ tSelf,    A,  B,  C,  D,  E,  F,  G,  H,  I,  J, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P11(A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K) \
	{ tSelf,    A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P12(A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L) \
	{ tSelf,    A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L, -1, -1, -1, -1, -1, -1, -1 }
#	define P13(A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M) \
	{ tSelf,    A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M, -1, -1, -1, -1, -1, -1 }
#	define P14(A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N) \
	{ tSelf,    A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N, -1, -1, -1, -1, -1 }
#	define P15(A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O) \
	{ tSelf,    A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O, -1, -1, -1, -1 }
#	define P16(A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,  P) \
	{ tSelf,    A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,  P, -1, -1, -1 }
#	define P17(A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,  P,  Q) \
	{ tSelf,    A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,  P,  Q, -1, -1 }
#	define P18(A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,  P,  Q,  R) \
	{ tSelf,    A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,  P,  Q,  R, -1 }
#	define P19(A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,  P,  Q,  R,  S) \
	{ tSelf,    A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,  P,  Q,  R,  S }
#else
#	define P0 \
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P1( A) \
	{ A, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P2( A,  B) \
	{ A,  B, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P3( A,  B,  C) \
	{ A,  B,  C, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P4( A,  B,  C,  D) \
	{ A,  B,  C,  D, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P5( A,  B,  C,  D,  E) \
	{ A,  B,  C,  D,  E, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P6( A,  B,  C,  D,  E,  F) \
	{ A,  B,  C,  D,  E,  F, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P7( A,  B,  C,  D,  E,  F,  G) \
	{ A,  B,  C,  D,  E,  F,  G, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P8( A,  B,  C,  D,  E,  F,  G,  H) \
	{ A,  B,  C,  D,  E,  F,  G,  H, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P9( A,  B,  C,  D,  E,  F,  G,  H,  I) \
	{ A,  B,  C,  D,  E,  F,  G,  H,  I, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P10(A,  B,  C,  D,  E,  F,  G,  H,  I,  J) \
	{ A,  B,  C,  D,  E,  F,  G,  H,  I,  J, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P11(A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K) \
	{ A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K, -1, -1, -1, -1, -1, -1, -1, -1 }
#	define P12(A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L) \
	{ A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L, -1, -1, -1, -1, -1, -1, -1 }
#	define P13(A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M) \
	{ A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M, -1, -1, -1, -1, -1, -1 }
#	define P14(A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N) \
	{ A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N, -1, -1, -1, -1, -1 }
#	define P15(A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O) \
	{ A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O, -1, -1, -1, -1 }
#	define P16(A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,  P) \
	{ A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,  P, -1, -1, -1 }
#	define P17(A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,  P,  Q) \
	{ A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,  P,  Q, -1, -1 }
#	define P18(A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,  P,  Q,  R) \
	{ A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,  P,  Q,  R, -1 }
#	define P19(A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,  P,  Q,  R,  S) \
	{ A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,  P,  Q,  R,  S }
#endif

#endif
