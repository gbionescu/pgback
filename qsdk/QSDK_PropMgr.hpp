#ifndef QSDK_QSDK_PROPMGR_HPP_
#define QSDK_QSDK_PROPMGR_HPP_
#include <vector>

#include "QSDK_Property.hpp"

class PropMgr
{
    std::vector<Property*> propList;
public:
    PropMgr();
    virtual ~PropMgr();

    virtual Property * getProperty(const char * name, prop_type type);
    virtual void deleteProperty(const char * name);
    virtual void clearProperties(void);
    virtual void printAllProps(void);

    virtual int32_t  getProperty_int32(const char * name);
    virtual void     setProperty_int32(const char * name, int32_t value);

    virtual void *   getProperty_ptr(const char * name);
    virtual void     setProperty_ptr(const char * name, void * data);

    virtual char *   getProperty_string(const char * name);
    virtual void     setProperty_string(const char * name, const char * value);

    virtual void *   getProperty_raw(const char * name);
    virtual void     setProperty_raw(const char * name, int32_t size, void * data);

    virtual uint32_t  getProperty_size(const char * name);
    virtual prop_type getProperty_type(const char * name);

private:
    virtual void addProperty(const char * name, const char * string);
    virtual void addProperty(const char * name, int32_t value);
    virtual void addProperty(const char * name, int32_t size, void * data);
    virtual void addProperty(const char * name, int32_t size, void * data, prop_type type);
};

#endif /* QSDK_QSDK_PROPMGR_HPP_ */
