#include <stdlib.h>
#include <stdio.h>
#include "QSDK_PyInterface.hpp"
#include "qsdk_if.h"
#include "util.h"

typedef struct py_init_data_
{
    PyObject * dev_init;
    PyObject * dev_inst;
    PyObject * dev_delete;
    PyObject * dev_read;
    PyObject * dev_write;
    PyObject * py_init_data;
    void * dev_init_result;
} py_init_data_t;

static PyObject * set_callbacks(PyObject * dummy, PyObject * args, PyObject * kwargs);
static PyObject * py_set_io_operations(PyObject * dummy, PyObject * args);
static PyObject * py_qsdk_set_mr(PyObject * dummy, PyObject * args);
static PyObject * py_alloc_memory_region(void);

PyMethodDef py_to_c_methods[] =
{
    {"py_register_device",      (PyCFunction)set_callbacks,             METH_VARARGS | METH_KEYWORDS},
    {"py_alloc_memory_region",  (PyCFunction)py_alloc_memory_region,    METH_VARARGS | METH_KEYWORDS},
    {"py_qsdk_set_mr",          (PyCFunction)py_qsdk_set_mr,            METH_VARARGS | METH_KEYWORDS},
    {"py_set_io_operations",    (PyCFunction)py_set_io_operations,      METH_VARARGS | METH_KEYWORDS},
    {NULL, NULL, 0, NULL}
};

static PyObject * callPyFunc(PyObject * func, PyObject * args)
{
    PyThreadState *_save;

    _save = PyEval_SaveThread();

    PyGILState_STATE gstate = PyGILState_Ensure();
    PyObject * pValue;
    pValue = PyObject_CallObject(func, args);

    if (pValue == NULL)
    {
        PyErr_Print();
    }

    PyGILState_Release(gstate);
    PyEval_RestoreThread(_save);

    return pValue;
}

/* TODO: interface functions are mostly the same - should be able to use unique mechanism for generating them dinamically */
static PyObject * py_alloc_memory_region(void)
{
    void * new_mr = alloc_memory_region();
    Py_INCREF(new_mr);

    return Py_BuildValue("O", new_mr);
}

static PyObject * py_qsdk_set_mr(PyObject * dummy, PyObject * args)
{
    Device * dev;
    void * mr;

    if (!PyArg_ParseTuple(args, "OO", &dev, &mr))
    {
        return NULL;
    }

    qsdk_set_mr(dev, mr);
    return Py_BuildValue("");
}

static void py_gen_write(void * opaque, int64_t offset, uint64_t value, unsigned size)
{
    py_init_data_t * dev_data = (py_init_data_t *)opaque;

    PyObject * arglist = Py_BuildValue("OLLi", dev_data->dev_init_result, offset, value, size);
    PyObject * ret = callPyFunc(dev_data->dev_write, arglist);
    Py_XDECREF(arglist);

    if (!ret)
    {
        /* TODO: handle EINTR */
        Py_XDECREF(ret);
    }
}

static uint64_t py_gen_read(void * opaque, int64_t offset, unsigned size)
{
    int64_t ret_val = 0;
    py_init_data_t * dev_data = (py_init_data_t *)opaque;

    PyObject * arglist = Py_BuildValue("OLi", dev_data->dev_init_result, offset, size);
    PyObject * ret = callPyFunc(dev_data->dev_read, arglist);
    Py_DECREF(arglist);

    PyArg_ParseTuple(ret, "L", &ret_val);

    if (!ret)
    {
        Py_DECREF(ret);
    }

    return ret_val;
}

static PyObject * py_set_io_operations(PyObject * dummy, PyObject * args)
{
    PyObject * dev;
    PyObject * read;
    PyObject * write;
    PyObject * size;

    if (!PyArg_ParseTuple(args, "OOOi", &dev, &read, &write, &size))
    {
        return NULL;
    }

    py_init_data_t * dev_data = (py_init_data_t*)get_property_ptr((Device *)dev, QSDK_PAYLOAD_IDENT);
    dev_data->dev_read = read;
    dev_data->dev_write = write;

    set_io_operations(
            (Device*)dev,
            (uint64_t (*)(void *, int64_t, unsigned int))py_gen_read,
            (void (*)(void *, int64_t, uint64_t, unsigned int))py_gen_write,
            (int64_t)size);

    return Py_BuildValue("");
}

static void * py_gen_init(void * dev, void * init_data)
{
    PyObject * ret_obj;
    py_init_data_t * dev_data = (py_init_data_t *)init_data;

    PyObject * arglist = Py_BuildValue("OO", dev, dev_data->py_init_data);
    PyObject * ret = callPyFunc(dev_data->dev_init, arglist);
    PyArg_ParseTuple(ret, "O", &ret_obj);
    Py_DECREF(arglist);

    dev_data->dev_init_result = ret_obj;

    return dev_data;
}

static void py_gen_inst(void * dev, void * opaque)
{
    py_init_data_t * dev_data = (py_init_data_t *)opaque;

    PyObject * arglist = Py_BuildValue("OO", dev, dev_data->dev_init_result);
    PyObject * ret = callPyFunc(dev_data->dev_inst, arglist);
    Py_DECREF(arglist);

    if (!ret)
    {
        Py_DECREF(ret);
    }
}

static void register_dev_from_py(
        char * name,
        PyObject * dev_init,
        PyObject * dev_inst,
        PyObject * dev_delete,
        PyObject * init_data
        )
{
    py_init_data_t * dev_data = (py_init_data_t *)QZALLOC(sizeof(py_init_data_t));
    dev_data->dev_init = dev_init;
    dev_data->dev_inst = dev_inst;
    dev_data->dev_delete = dev_delete;
    dev_data->py_init_data = init_data;

    dev_init_t logger;

    logger.name = name;
    logger.dev_init = py_gen_init;
    logger.dev_inst = py_gen_inst;
    logger.dev_delete = NULL;
    logger.init_data = dev_data;

    register_device(&logger);
}

static PyObject * set_callbacks(PyObject * dummy, PyObject * args, PyObject * kwargs)
{
    char * name;
    PyObject * dev_init;
    PyObject * dev_inst;
    PyObject * dev_delete;
    PyObject * init_data;

    static char* kwlist[] = {
            (char*)"name",
            (char*)"dev_init",
            (char*)"dev_inst",
            (char*)"dev_delete",
            (char*)"init_data",
            NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "sOOOO",
                     kwlist, &name, &dev_init, &dev_inst, &dev_delete, &init_data))
    {
        return NULL;
    }

    if (!PyCallable_Check(dev_init)) {
        PyErr_SetString(PyExc_TypeError, "parameter dev_init must be callable");
        goto err;
    }

    if (!PyCallable_Check(dev_inst)) {
        PyErr_SetString(PyExc_TypeError, "parameter dev_inst must be callable");
        goto err;
    }

    Py_XINCREF(dev_init);
    Py_XINCREF(dev_inst);
    Py_XINCREF(dev_delete);
    Py_XINCREF(init_data);

    register_dev_from_py(name, dev_init, dev_inst, dev_delete, init_data);
    return Py_None;

    err:
    Py_XDECREF(dev_init);
    Py_XDECREF(dev_inst);
    Py_XDECREF(dev_delete);
    return NULL;
}

int init_py_functions(void)
{
    PyObject * ret = Py_InitModule("pgback", py_to_c_methods);

    return ret != NULL;
}
