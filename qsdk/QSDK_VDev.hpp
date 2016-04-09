#ifndef QSDK_QSDK_VDEV_HPP_
#define QSDK_QSDK_VDEV_HPP_
#ifndef __cplusplus
#error ".hpp files should not be included in C files!"
#endif
#include "QSDK_PropMgr.hpp"
#include "QSDK_Device.hpp"
#include "QSDK_RDev.hpp"
#include "qsdk_if.h"

class VDev : public Device
{
private:
    RDev * rdev;
    bool instantiated;

public:
    VDev();
    VDev(const char * name, const char * type);

    mem_region getMR();
    RDev * getRDev();

    void printDevice(void);
    void runInstantiate(void);

    virtual ~VDev();
};

#endif /* QSDK_QSDK_VDEV_HPP_ */
