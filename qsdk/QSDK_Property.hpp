#ifndef QSDK_QSDK_PROPERTY_HPP_
#define QSDK_QSDK_PROPERTY_HPP_
#include "QSDK_types.h"

class Property
{
private:
    char * name;
    int32_t size;
    void * data;
    prop_type type;

public:
    Property();
    Property(const char * name, int32_t size, void * data, prop_type type);

    prop_type getType(void);
    void * getData(void);
    int32_t getSize(void);
    bool isNamedProp(const char * name);
    void printProperty(void);

    virtual ~Property();
};

#endif /* QSDK_QSDK_PROPERTY_HPP_ */
