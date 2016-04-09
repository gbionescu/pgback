#ifndef QSDK_QSDK_RDEV_HPP_
#define QSDK_QSDK_RDEV_HPP_
#ifndef __cplusplus
#error ".hpp files should not be included in C files!"
#endif
#include "QSDK_Device.hpp"
#include "qsdk_if.h"

class RDev : public Device
{
    friend class VDev;
public:
    RDev(dev_init_t * dev, dtype type);

private:
    RDev();
    virtual ~RDev();

    void printDevice(void);
    void * initialize(void * payload);
    void * instantiate(void * payload, void * init_data);
};

#endif /* QSDK_QSDK_RDEV_HPP_ */
