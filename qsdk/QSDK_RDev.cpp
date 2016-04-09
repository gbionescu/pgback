#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "QSDK_RDev.hpp"
#include "util.h"

#define PROP_INIT_DATA        "initData"
#define PROP_DEV_INIT         "initEntryPoint"
#define PROP_DEV_INST         "instEntryPoint"
#define PROP_DEV_DELETE       "deleteEntryPoint"

typedef void * (init_ep)(void *, void *);
typedef void * (inst_ep)(void *, void *);

RDev::RDev()
{
    this->type = QSDK_NONE;
}

RDev::~RDev()
{
}

void RDev::printDevice(void)
{
    int i = 0;
    cppprint("RDev %s of type %d with %s 0x%x %s 0x%x\n",
            this->getName(), this->type,
            PROP_DEV_INIT,
            *(int*)this->props.getProperty(PROP_DEV_INIT, PROP_PTR)->getData(),
            PROP_DEV_INST,
            *(int*)this->props.getProperty(PROP_DEV_INST, PROP_PTR)->getData()
            );

    this->props.printAllProps();
}

RDev::RDev(dev_init_t * dev, dtype type)
: Device(dev->name, type)
{
    this->props.setProperty_ptr(PROP_INIT_DATA,  (void*)dev->init_data);
    this->props.setProperty_ptr(PROP_DEV_INIT,   (void*)dev->dev_init);
    this->props.setProperty_ptr(PROP_DEV_INST,   (void*)dev->dev_inst);
    this->props.setProperty_ptr(PROP_DEV_DELETE, (void*)dev->dev_delete);
}

void * RDev::initialize(void * payload)
{
    Property * dinit = this->props.getProperty(PROP_DEV_INIT, PROP_PTR);

    if (dinit)
    {
        init_ep * ep = (init_ep*)(*(size_t*)dinit->getData());
        if (ep)
        {
            Property * idata = this->props.getProperty(PROP_INIT_DATA, PROP_PTR);
            return ep(payload, (void*)*(size_t*)idata->getData());
        }
        else
        {
            cppprint("NULL initiate ptr in %s\n", this->getName());
        }
    }

    return NULL;
}

/* These should not be called from something else than a vdev FIXME */
void * RDev::instantiate(void * payload, void * init_data)
{
    Property * prop = this->props.getProperty(PROP_DEV_INST, PROP_PTR);

    if (prop)
    {
        inst_ep * ep = (inst_ep*)(*(size_t*)prop->getData());
        if (ep)
        {
            return ep(payload, init_data);
        }
        else
        {
            cppprint("NULL instante ptr in %s\n", this->getName());
        }
    }

    return NULL;
}

extern "C" void add_device(dev_init_t * dev)
{
    new RDev(dev, QSDK_RDEV);
}

extern "C" void add_board(dev_init_t * dev)
{
    new RDev(dev, QSDK_BOARD);
}

