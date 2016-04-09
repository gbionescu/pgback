#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <Python.h>
#include "qsdk/QSDK_DevMgr.hpp"
#include "qsdk/QSDK_LibLoader.hpp"
#include "qsdk/QSDK_PyLoader.hpp"
#include "QSDK_VDev.h"
#include "qsdk_qemu_gateway.h"

extern "C" {
void launch_board(const char * name, const char * kernel);
void lib_qsdk_init(void * board);
}

static void bexec(Device * dev, dtype type)
{
    register_qsdk_board(dev->getName());
}

static void foreach_board(void (*exec)(Device*, dtype))
{
    DevMgr::getInstance().runForEachDevOfType(bexec, QSDK_BOARD);
}


void lib_qsdk_init(void * board)
{
    initPyEnv();

    /* Load dynamic devices */
    initLibLoader();
    loadDynDevs("./lib");

    DevMgr::getInstance().printAllDevs();
    foreach_board(bexec);
}

void launch_board(const char * name, const char * kernel)
{
    Device * board_create = vdev_create("main_board", name);
    set_property_string(board_create, "kernel_file", kernel);

    vdev_instantiate_by_ref(board_create);
}
