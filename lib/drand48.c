/*
 * Copyright (c) 1993 Martin Birgmeier
 * All rights reserved.
 *
 * You may redistribute unmodified or modified versions of this source
 * code provided that the above copyright notice and this and the
 * following conditions are retained.
 *
 * This software is provided ``as is'', and comes with no warranties
 * of any kind. I shall in no event be liable for anything that happens
 * to anyone/anything when using this software.
 *
 * $FreeBSD$
 */
/*
 * An implementation of rand48
 * modified from FreeBSD source.
 * 
 * David Palmer
 * Gene Codes Corp.
 */

#ifndef _RAND48_H_
#define _RAND48_H_

#if defined(__MINGW64__) || defined(__MINGW32__)

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include "drand48.h"

#define RAND48_SEED     (0x1234abcd330e)
#define RAND48_MULT     (0x0005deece66d)
#define RAND48_ADD      (0x000b)

uint64_t _rand48_seed =	RAND48_SEED;

static void
_dorand48(uint64_t *xseed)
{
	*xseed = (RAND48_MULT * (*xseed) + RAND48_ADD) & 0x0000FFFFFFFFFFFF;
}

double
erand48(uint64_t *xseed)
{
	_dorand48(xseed);
	return ldexp((double) *xseed, -48);
}

double
drand48(void)
{
	return erand48(&_rand48_seed);
}

long
lrand48(void)
{
	_dorand48(&_rand48_seed);
	return ((long)_rand48_seed) >> 1;
}

void
srand48(long int seedval)
{
    _rand48_seed = (((uint64_t) seedval) << 16) | 0x330E;
}

#endif

#endif /* _RAND48_H_ */
