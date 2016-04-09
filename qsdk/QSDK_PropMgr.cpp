#include "QSDK_PropMgr.hpp"

#include <stdlib.h>
#include <stdio.h>
#include "util.h"

PropMgr::PropMgr()
{
}

PropMgr::~PropMgr()
{

}

void PropMgr::addProperty(const char * name, const char * string)
{
    this->propList.push_back(new  Property(name, QSTRLEN(string) + 1, (void*)string, PROP_STRING));
}

void PropMgr::addProperty(const char * name, int32_t value)
{
    this->propList.push_back(new  Property(name, sizeof(int32_t), &value, PROP_INT32));
}

void PropMgr::addProperty(const char * name, int32_t size, void * data)
{
    this->propList.push_back(new  Property(name, size, data, PROP_RAW));
}

void PropMgr::addProperty(const char * name, int32_t size, void * data, prop_type type)
{
    this->propList.push_back(new  Property(name, size, data, type));
}

Property * PropMgr::getProperty(const char * name, prop_type type)
{
    for (std::vector<Property*>::iterator it = this->propList.begin(); it != this->propList.end(); it++)
    {
        if ((*it)->isNamedProp(name))
        {
            if ((*it)->getType() & type)
            {
                return *it;
            }
            else
            {
                cppprint("Property [%s] is of type %d but request was for %d!\n", name, (int)(*it)->getType(), (int)type);
            }
        }
    }
    cppprint("Property [%s] not found!\n", name);
    return NULL;
}

void PropMgr::deleteProperty(const char * name)
{
    for (std::vector<Property*>::iterator it = this->propList.begin(); it != this->propList.end(); it++)
    {
        if ((*it)->isNamedProp(name))
        {
            this->propList.erase(it);
        }
    }
}

void PropMgr::clearProperties(void)
{
    this->propList.clear();
}

void PropMgr::printAllProps(void)
{
    for (std::vector<Property*>::iterator it = this->propList.begin(); it != this->propList.end(); it++)
    {
        (*it)->printProperty();
    }
}

int32_t PropMgr::getProperty_int32(const char* name)
{
    Property * prop = getProperty(name, PROP_INT32);

    if (prop)
    {
        return *(int32_t*)prop->getData();
    }

    return 0;
}

char* PropMgr::getProperty_string(const char* name)
{
    Property * prop = getProperty(name, PROP_STRING);

    if (prop)
    {
        return (char*)prop->getData();
    }

    return NULL;
}

void PropMgr::setProperty_int32(const char * name, int32_t value)
{
    addProperty(name, value);
}

void PropMgr::setProperty_string(const char * name, const char * value)
{
    addProperty(name, value);
}

void * PropMgr::getProperty_raw(const char* name)
{
    Property * prop = getProperty(name, PROP_RAW);

    if (prop)
    {
        return (void*)prop->getData();
    }

    return NULL;
}

void PropMgr::setProperty_raw(const char* name, int32_t size, void * data)
{
    addProperty(name, size, data);
}


void * PropMgr::getProperty_ptr(const char* name)
{
    Property * prop = getProperty(name, PROP_PTR);

    if (prop)
    {
        return (void*)*(intptr_t*)prop->getData();
    }

    return NULL;
}

void PropMgr::setProperty_ptr(const char* name, void * data)
{
    addProperty(name, sizeof(void*), &data, PROP_PTR);
}

uint32_t PropMgr::getProperty_size(const char* name)
{
    Property * prop = getProperty(name, PROP_ANY);

    if (prop)
    {
        return (uint32_t)prop->getSize();
    }

    return 0;
}

prop_type PropMgr::getProperty_type(const char* name)
{
    Property * prop = getProperty(name, PROP_ANY);

    if (prop)
    {
        return prop->getType();
    }

    return PROP_NONE;
}
