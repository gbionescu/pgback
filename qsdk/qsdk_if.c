#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "qsdk_if.h"
#include "qsdk_qemu_gateway.h"
#include "QSDK_RDev.h"
#include "QSDK_VDev.h"

#define DBG_FUNC() printf("called %s\n", __FUNCTION__);

void set_io_operations(
        void * dev,
        uint64_t (*read)(void * opaque, int64_t addr, unsigned size),
        void (*write)(void *opaque, int64_t addr, uint64_t data, unsigned size),
        int size)
{
    void * ops = init_memory_region_ops(read, write);

    /* TODO: warn if size > how it's mapped onto the target memory */

    memory_region_init_io(qsdk_get_mr(dev), NULL, ops, get_property_ptr(dev, QSDK_PAYLOAD_IDENT), "", size);
}

mem_region alloc_memory_region(void)
{
    return QSDK_alloc_memory_region();
}

mem_region * get_sysmem()
{
    return get_system_memory();
}

void register_device(dev_init_t * dev_info)
{
    add_device(dev_info);
}

void register_board(dev_init_t * dev_info)
{
    add_board(dev_info);
}

Device * create_device(const char * name, const char * type)
{
    return vdev_create(name, type);
}

void map_device_to_memory(Device * dev, mem_region mr, uint64_t offset, uint64_t size)
{
    set_property_int32(dev, QSDK_DEVICE_OFFS, offset);
    set_property_int32(dev, QSDK_DEVICE_SIZE, size);
    set_property_ptr(dev, QSDK_DEVICE_HMEM, mr);

    instantiate_device(dev);

    memory_region_add_subregion(mr, offset, qsdk_get_mr(dev));
}

void set_read_op(mem_region * mr, uint64_t (*read)(void * opaque, int64_t addr, unsigned size))
{
    assert(0);
}

void set_write_op(mem_region * mr, void (*write)(void *opaque, int64_t addr, uint64_t data, unsigned size))
{
    assert(0);
}

void map_to_targetmem(mem_region * targetmem, mem_region * region, int64_t offset)
{
    assert(0);
}

static void instantiator(Device * dev)
{
    instantiate_device(dev);
}

void instantiate_devices(void)
{
    vdev_foreach(instantiator);
}

void instantiate_device(Device * dev)
{
    vdev_instantiate_by_ref(dev);
}

int32_t get_property_int32(Device * dev, const char * name)
{
    return vdev_get_property_int32(dev, name);
}

void set_property_int32(Device * dev, const char * name, int32_t value)
{
    vdev_set_property_int32(dev, name, value);
}

char * get_property_string(Device * dev, const char * name)
{
    return vdev_get_property_string(dev, name);
}

void set_property_raw(Device * dev, const char * name, uint32_t size, void * data)
{
    vdev_set_property_raw(dev, name, size, data);
}

void * get_property_raw(Device * dev, const char * name)
{
    return vdev_get_property_raw(dev, name);
}

void set_property_ptr(Device * dev, const char * name, void * ptr)
{
    vdev_set_property_ptr(dev, name, ptr);
}

void * get_property_ptr(Device * dev, const char * name)
{
    return vdev_get_property_ptr(dev, name);
}

void set_property_string(Device * dev, const char * name, const char * value)
{
    vdev_set_property_string(dev, name, value);
}

uint32_t get_property_size(Device * dev, const char * name)
{
    return vdev_get_property_size(dev, name);
}

void qsdk_set_mr(Device * dev, void * mr)
{
    set_property_ptr(dev, QSDK_MR_IDENTIFIER, mr);
}

void * qsdk_get_mr(Device * dev)
{
    return get_property_ptr(dev, QSDK_MR_IDENTIFIER);
}


