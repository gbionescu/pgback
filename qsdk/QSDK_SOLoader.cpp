#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <dlfcn.h>
#include <vector>
#include "util.h"

#define DEVICE_EP_NAME "init_qsdk_module"

static std::vector<void*> openedHandles;

int loadSOFile(const char * path, const char * fname)
{
    char * error;
    void (* dev_init)();

    std::string fullPath = std::string(path) + std::string("/") + std::string(fname);

    cprint("Loading .so file: %s... \n", fullPath.data());

    void * handle = dlopen(fullPath.data(), RTLD_NOW | RTLD_GLOBAL);
    if (!handle)
    {
        fputs (dlerror(), stderr);
        return -1;
    }

    dev_init = (void(*)())dlsym(handle, DEVICE_EP_NAME);

    if ((error = dlerror()) != NULL)
    {
        fputs(error, stderr);
        return -1;
    }
    else
    {
        if (dev_init)
        {
            cprint("Found entry point for a device.\n");
            (*dev_init)();
        }
        else
        {
            cprint("Could not find dev handler for %s\n", fullPath.data());
            return -1;
        }
    }

    openedHandles.push_back(handle);
    cprint("Done!\n");
    return 0;
}
