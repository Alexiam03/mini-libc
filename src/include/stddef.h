/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef __STDDEF_H__
#define __STDDEF_H__	1

#include <internal/types.h>
#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long size_t;
#endif

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
typedef long ptrdiff_t;
#endif

#endif
