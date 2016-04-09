#ifndef QSDK_DEVICE_HPP_
#define QSDK_DEVICE_HPP_
#include "QSDK_PropMgr.hpp"
#include "QSDK_types.h"

class Device
{
public:
    Device();
    virtual ~Device();

    Device(const char* name, dtype type);

    void setName(const char * name);
    char * getName(void);
    bool isNamed(const char * name);

    virtual dtype getType(void);
    virtual void printDevice(void) = 0;

    PropMgr props; /* Should be protected too */

protected:
    dtype type;
};

#endif /* QSDK_qdev_H_ */
