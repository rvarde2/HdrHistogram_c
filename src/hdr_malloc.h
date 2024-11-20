/**
 * hdr_malloc.h
 * Written by Filipe Oliveira and released to the public domain,
 * as explained at http://creativecommons.org/publicdomain/zero/1.0/
 *
 * Allocator selection.
 *
 * This file is used in order to change the HdrHistogram allocator at compile time.
 * Just define the following defines to what you want to use. Also add
 * the include of your alternate allocator if needed (not needed in order
 * to use the default libc allocator). */

#ifndef HDR_MALLOC_H__
#define HDR_MALLOC_H__

#include <rte_malloc.h>
#include <rte_memcpy.h>
#define hdr_malloc(MEM_SIZE) rte_malloc(NULL,MEM_SIZE,64)
#define hdr_calloc(N,TYPE_SIZE) rte_calloc(NULL, N, TYPE_SIZE, 64)
#define hdr_realloc(PTR,NEW_SIZE) rte_realloc(PTR,NEW_SIZE,64)
#define hdr_free(VAR) rte_free(VAR)

#define hdr_memcpy rte_memcpy

#endif
