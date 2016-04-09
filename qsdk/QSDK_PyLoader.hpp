#ifndef QSDK_QSDK_PYLOADER_HPP_
#define QSDK_QSDK_PYLOADER_HPP_
#include "Python.h"

void initPyEnv(void);
void finalizePyEnv(void);
int loadPYCFile(const char * path, const char * file);

#endif /* QSDK_QSDK_PYLOADER_HPP_ */
