#if !defined(__i386__) && !defined(_M_IX86) && !defined(_M_X64)
#error "Make sure this is configured correctly for target architecture."
#endif

#define IEEE_8087
#define Arith_Kind_ASL 1