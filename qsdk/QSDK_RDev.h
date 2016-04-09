#ifndef QSDK_QSDK_RDEV_H_
#define QSDK_QSDK_RDEV_H_
#include "qsdk_if.h"

#ifdef __cplusplus
extern "C"
{
#endif

void add_device(dev_init_t * dev);
void add_board(dev_init_t * dev);

#ifdef __cplusplus
}
#endif

#endif /* QSDK_QSDK_RDEV_H_ */
