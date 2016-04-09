#ifndef QSDK_TYPES_H_
#define QSDK_TYPES_H_
#include <stdint.h>

typedef enum
{
    PROP_NONE    = (1 << 0),
    PROP_RAW     = (1 << 1),
    PROP_PTR     = (1 << 2),
    PROP_INT32   = (1 << 3),
    PROP_STRING  = (1 << 4),

    PROP_ANY     = (0xFFFFFFFF)
} prop_type;

typedef enum
{
    QSDK_NONE,
    QSDK_BOARD,
    QSDK_RDEV,
    QSDK_VDEV
} dtype;

#define PROP_NAME_IDENTIFIER "name"

#endif
