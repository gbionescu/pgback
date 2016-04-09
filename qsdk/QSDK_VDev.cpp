#include <stdlib.h>
#include <stdexcept>
#include "QSDK_VDev.hpp"
#include "QSDK_VDev.h"
#include "QSDK_RDev.h"
#include "qsdk_qemu_gateway.h"
#include "QSDK_DevMgr.hpp"
#include "qsdk_if.h"
#include "util.h"

VDev::VDev()
{
    rdev = NULL;
    instantiated = false;
}

VDev::VDev(const char * name, const char * type)
: Device(name, QSDK_VDEV)
{
    rdev = (RDev*)DevMgr::getInstance().getRegisteredDevice(type);

    if (NULL == rdev)
    {
        throw std::invalid_argument("invalid device requested");
    }

    instantiated = false;
    props.setProperty_ptr(QSDK_PAYLOAD_IDENT, rdev->initialize(this));
}

void VDev::printDevice(void)
{
    cppprint("%s TODO\n", __FUNCTION__);
}

RDev * VDev::getRDev()
{
    return this->rdev;
}

void VDev::runInstantiate(void)
{
    if (!instantiated)
    {
        instantiated = true;
        rdev->instantiate(this, props.getProperty_ptr(QSDK_PAYLOAD_IDENT));
    }
    else
    {
        cppprint("VDev %s already instantiated.\n", rdev->getName());
    }
}

VDev::~VDev()
{
}

Device * vdev_create(const char * name, const char * type)
{
    return new VDev(name, type);
}

int32_t vdev_get_property_int32(Device * dev, const char * name)
{
    return ((VDev*)dev)->props.getProperty_int32(name);
}

void vdev_set_property_int32(Device * dev, const char * name, int32_t value)
{
    ((VDev*)dev)->props.setProperty_int32(name, value);
}

char * vdev_get_property_string(Device * dev, const char * name)
{
    return ((VDev*)dev)->props.getProperty_string(name);
}

void vdev_set_property_string(Device * dev, const char * name, const char * value)
{
    ((VDev*)dev)->props.setProperty_string(name, value);
}

void * vdev_get_property_raw(Device * dev, const char * name)
{
    return ((VDev*)dev)->props.getProperty_raw(name);
}

void vdev_set_property_raw(Device * dev, const char* name, uint32_t size,
        void* src)
{
    ((VDev*)dev)->props.setProperty_raw(name, size, src);
}

void* vdev_get_property_ptr(Device * dev, const char * name)
{
    return ((VDev*)dev)->props.getProperty_ptr(name);
}

void vdev_set_property_ptr(Device * dev, const char * name, void * ptr)
{
    ((VDev*)dev)->props.setProperty_ptr(name, ptr);
}

uint32_t vdev_get_property_size(Device * dev, const char * name)
{
    return ((VDev*)dev)->props.getProperty_size(name);
}

void * vdev_get_created_object(const char * name)
{
    return DevMgr::getInstance().getVirtualDeviceNamed(name);
}

void * vdev_get_object_of_type(const char * type)
{
    /* TODO */
    return NULL;
}

void vdev_instantiate_by_ref(Device * dev)
{
    ((VDev*)dev)->runInstantiate();
}

void vdev_foreach(void (*exec)(Device *))
{
    DevMgr::getInstance().runForEachVDev(exec);
}
