#ifndef QSDK_UTIL_H_
#define QSDK_UTIL_H_
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "util_d.h"

#define QABORT()                abort();
#define QASSERT(cond)           assert(cond)
#define QMALLOC(size)           malloc(size)
#define QFREE(ptr)              free(ptr)
#define QZALLOC(size)           calloc(1, size)
#define QMEMCPY(dst, src, size) if (dst && src) {memcpy(dst, src, size);}

#define QSTRDUP(ptr)            strdup(ptr)
#define QSTRLEN(ptr)            strlen(ptr)
#define QSTRCMP(a, b)           strcmp(a, b)

#endif /* QSDK_UTIL_H_ */
