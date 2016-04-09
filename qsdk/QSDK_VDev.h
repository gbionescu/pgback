#ifndef QSDK_QSDK_VDEV_H_
#define QSDK_QSDK_VDEV_H_
#include "qsdk_if.h"

#ifdef __cplusplus
extern "C"
{
#endif

Device *  vdev_create(const char * name, const char * type);
void *  vdev_get_created_object(const char * name);

void *  vdev_get_property_raw(Device * dev, const char * name);
void    vdev_set_property_raw(Device * dev, const char * name, uint32_t size, void * src);

int32_t vdev_get_property_int32(Device * dev, const char * name);
void    vdev_set_property_int32(Device * dev, const char * name, int32_t value);

void *  vdev_get_property_ptr(Device * dev, const char * name);
void    vdev_set_property_ptr(Device * dev, const char * name, void * ptr);

char *  vdev_get_property_string(Device * dev, const char * name);
void    vdev_set_property_string(Device * dev, const char * name, const char * value);

uint32_t vdev_get_property_size(Device * dev, const char * name);

void vdev_foreach(void (*callback)(Device * dev));
void vdev_instantiate_by_ref(Device * dev);

#ifdef __cplusplus
}
#endif

#endif /* QSDK_QSDK_VDEV_H_ */
