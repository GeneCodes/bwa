BWA for Windows -- v0.7.5a
=========================

Source Code Modifications
-------------------------

BWA was designed for compilation under UNIX/POSIX-compliant systems.  To compile it under Windows, some changes to its source code were made:

1.	The 32-bit fixed-width unsigned integer type referred to on the following lines
		
		bwt_lite.c:47
		bwtgap.c:57
		bwtgap.h:8,9,10
		bwtmisc.c:93
		
	was changed from `u_int32_t` to `uint32_t` to comply with the C standard.  The
	`u_int` types are not defined on MinGW-w64.
2.	A call to `index` was replaced with a call to the equivalent function
	`strchr` on line 160 of `bwaseqio.c` to better comply with the ISO C standard.
3.	`fsync()` does nto exist on Windows.  The equivalent function is `_commit()`.  `fsync`
	was defined as `commit` in `utils.c`.
4.	The `rand48` family of pseudorandom number generators is not included in MinGW-w64.
	A custom implementation, adapted from the FreeBSD sources, was borrowed from my
	Windows port of Maq 0.7.1.  This implementation comprises the files `lib/drand48.h`
	and `lib/drand48.c`.  The function `lrand48()`, which generates
	an unsigned integer between `0` and `2^31 - 1`, was added.  The files
		
		bntseq.c
		bwape.c
		bwase.c
		bwtsw2_main.c
		
	were modified by the addition of a conditional inclusion:
	
		#if defined(__MINGW64__) || defined(__MINGW32__)
		#include "lib/drand48.h"
		#endif
		
5.	A Windows implementation of `cputime()` was added to `utils.c`.
	`cputime()` now calls `getrusage() on UNIX and `GetProcessTimes()` on
	Windows.  The Windows implementation was adapted from the Windows port of Maq.
	The timing functionality in `bwtsw2_core.c` was modified to use this cross-platform
	timer.  In particular, calls to `getrusage()` were replaced by calls to `cputime()`,
	and the `time_elapse()` function was removed and replaced with simple subtraction
	of double-precision floating point numbers.  The timing data in `bwtsw2_core.c` is
	never used (see lines 599-608, where times are printed in a commented-out `fprintf()` call).
	So these modifications could be removed without changing program functionality.
6.	The features used in `kopen.c` that do not work in MinGW--UNIX pipes and various networking
	functionality--were disabled for MinGW, and error messages were added.
7.	The `Makefile` was modified to add `lib/drand48.o` to `libbwa.a`.  `lib/drand48.c` was
	modified with
	
		#if defined(__MINGW64__) || defined(__MINGW32__)
		// ...
		// code here
		// ...
		#endif
	
	so that it will compile as if empty on Unix, and its functions will not conflict
	with those provided by the standard C library.
8.	`-static -msse2` was added to `CFLAGS` in `Makefile` so that the `winpthread` library
	will be linked statically and so that the functions that depend on SSE2 will compile
	in a 32-bit environment.
