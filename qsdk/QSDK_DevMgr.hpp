#ifndef QSDK_QSDK_DEVMGR_HPP_
#define QSDK_QSDK_DEVMGR_HPP_
#include <vector>
#include "QSDK_Device.hpp"

class DevMgr
{
public:
    static DevMgr& getInstance()
    {
        static DevMgr instance;
        return instance;
    }

    void registerDevice(Device * new_dev, dtype type);
    Device * getRegisteredDevice(const char * name);
    Device * getVirtualDeviceNamed(const char * name);

    void runForEachVDev(void (*exec)(Device*));
    void runForEachDevOfType(void (*exec)(Device*, dtype), dtype type);

    void printAllDevs(void);

private:
    DevMgr() {};
    DevMgr(DevMgr const&); /* Singleton - do not implement */

    std::vector<Device*> devs;
    std::vector<Device*> vdevs;
};

#endif /* QSDK_QSDK_DEVMGR_HPP_ */
