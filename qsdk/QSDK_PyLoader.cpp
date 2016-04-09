#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string>
#include <vector>
#include "QSDK_PyLoader.hpp"
#include "QSDK_PyInterface.hpp"
#include "qsdk_if.h"
#include "util.h"

static std::vector<PyObject*> loadedModules;
static bool pyENVUp = false;

int loadPYCFile(const char * path, const char * file)
{
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;
    std::string sfile = std::string(file);

    cprint("Loading python file %s\n", file);

    pName = PyUnicode_FromString(sfile.substr(0, sfile.rfind(".")).data());
    /* Error checking of pName left out */
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL)
    {
        pFunc = PyObject_GetAttrString(pModule, "init_qsdk_module");
        /* pFunc is a new reference */
        if (pFunc && PyCallable_Check(pFunc))
        {
            pValue = PyObject_CallObject(pFunc, NULL);

            if (pValue != NULL)
            {
                Py_DECREF(pValue);
            }
            else
            {
                Py_DECREF(pFunc);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }
        else
        {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function\n");
        }

        Py_XDECREF(pFunc);
    }
    else
    {
        PyErr_Print();
        fprintf(stderr, "Failed to load\n");
        return 1;
    }

    Py_XINCREF(pModule);
    loadedModules.push_back(pModule);

    cprint("Done!\n");

    return 0;
}

void initPyEnv(void)
{
    if (!pyENVUp)
    {
        if (!Py_IsInitialized())
        {
            Py_Initialize();
        }

        if (!PyEval_ThreadsInitialized())
        {
            PyEval_InitThreads();
        }

        init_py_functions();

        PyObject * sysPath = PySys_GetObject((char*)"path");
        PyObject * path = PyString_FromString("./lib/");
        int result = PyList_Insert(sysPath, 0, path);

        pyENVUp = true;
    }
}

void finalizePyEnv(void)
{
    Py_Finalize();
    pyENVUp = false;
}
