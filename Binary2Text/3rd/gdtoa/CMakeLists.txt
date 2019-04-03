cmake_minimum_required (VERSION 3.1) 
 
file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)

my_add_library(gdtoa
dmisc.c
dtoa.c
gdtoa.c
gethex.c
gmisc.c
g_dfmt.c
g_ffmt.c
g__fmt.c
hd_init.c
hexnan.c
misc.c
smisc.c
strtod.c
strtodg.c
strtof.c
strtord.c
sum.c
ulp.c
	${CURRENT_HEADERS}
)
 
