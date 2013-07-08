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

#ifdef __cplusplus
extern "C"
#endif

#include <stdint.h>

double erand48(uint64_t *xseed);
void srand48(long int seedval);
double drand48(void);
long lrand48(void);

#ifdef __cplusplus
}
#endif

#endif /* _RAND48_H_ */
