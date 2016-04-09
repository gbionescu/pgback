#include "QSDK_Device.hpp"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "QSDK_DevMgr.hpp"
#include "util.h"

Device::Device()
{
    this->type = QSDK_NONE;
}

bool Device::isNamed(const char * name)
{
    return QSTRCMP(getName(), name) == 0 ? true : false;
}

Device::~Device()
{
    this->props.clearProperties();
}

void Device::setName(const char * name)
{
    this->props.setProperty_string(PROP_NAME_IDENTIFIER, name);
}

Device::Device(const char * name, dtype type)
{
    this->type = type;
    this->setName(name);

    DevMgr::getInstance().registerDevice(this, type);
}

char * Device::getName(void)
{
    Property * pr = this->props.getProperty(PROP_NAME_IDENTIFIER, PROP_STRING);
    if (pr)
    {
        return (char*)pr->getData();
    }

    cppprint("Could not get name.");
    return NULL;
}

dtype Device::getType(void)
{
    return type;
}
