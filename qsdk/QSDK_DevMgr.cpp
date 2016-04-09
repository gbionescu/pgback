#include "QSDK_DevMgr.hpp"

#include <stdlib.h>
#include "QSDK_RDev.h"
#include "util.h"

void DevMgr::registerDevice(Device * new_dev, dtype type)
{
    switch (type)
    {
    case QSDK_BOARD: /* TODO: boards are registered the same way as devs */
    case QSDK_RDEV:
        this->devs.push_back(new_dev);
        break;
    case QSDK_VDEV:
        this->vdevs.push_back(new_dev);
        break;
    default:
        abort();
        break;
    }
}

Device * DevMgr::getRegisteredDevice(const char * name)
{
    for (std::vector<Device*>::iterator it = this->devs.begin(); it != this->devs.end(); it++)
    {
        if ((*it)->isNamed(name))
        {
            return *it;
        }
    }

    cppprint("Could not find %s\n", name);
    return NULL;
}

Device * DevMgr::getVirtualDeviceNamed(const char * name)
{
    for (std::vector<Device*>::iterator it = this->vdevs.begin(); it != this->vdevs.end(); it++)
    {
        if ((*it)->isNamed(name))
        {
            return *it;
        }
    }

    cppprint("Could not find %s\n", name);
    return NULL;
}

void DevMgr::printAllDevs(void)
{
    for (std::vector<Device*>::iterator it = this->devs.begin(); it != this->devs.end(); it++)
    {
        (*it)->printDevice();
    }
}

void DevMgr::runForEachVDev(void (*exec)(Device*))
{
    for (std::vector<Device*>::iterator it = this->vdevs.begin(); it != this->vdevs.end(); it++)
    {
        exec(*it);
    }
}

void DevMgr::runForEachDevOfType(void (*exec)(Device*, dtype), dtype type)
{
    for (std::vector<Device*>::iterator it = this->devs.begin(); it != this->devs.end(); it++)
    {
        if ((*it)->getType() == type)
        {
            exec(*it, (*it)->getType());
        }
    }
}
