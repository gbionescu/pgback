#include "QSDK_Property.hpp"

#include <stdio.h>
#include "util.h"

Property::Property(const char * name, int32_t size, void * data, prop_type type)
{
    this->name = QSTRDUP(name);
    this->data = QZALLOC(size);
    this->size = size;
    this->type = type;

    QMEMCPY(this->data, data, size);
}

Property::Property()
{
    this->name = NULL;
    this->data = NULL;
    this->size = 0;
    this->type = PROP_NONE;
}

Property::~Property()
{
    QFREE(this->name);
    QFREE(this->data);
}

prop_type Property::getType(void)
{
    return this->type;
}

bool Property::isNamedProp(const char * name)
{
    return QSTRCMP(this->name, name) == 0 ? true : false;
}

void* Property::getData(void)
{
    return this->data;
}

void Property::printProperty(void)
{
    int i = 0;

    printf("\tName: %s\n", this->name);
    printf("\tType: ");
    switch(this->type)
    {
    case PROP_NONE:
        printf("NONE\n");
        break;

    case PROP_INT32:
        printf("INT32\n");
        break;

    case PROP_STRING:
        printf("STRING\n");
        break;

    case PROP_RAW:
        printf("RAW\n");
        break;

    case PROP_PTR:
        printf("PTR\n");
        break;
    default:
        break;
    }

    printf("\tSize: %d\n", this->size);

    printf("\tData: ");
    switch(this->type)
    {
        case PROP_NONE:
            printf("No data for NONE type.\n");
            break;

        case PROP_INT32:
            printf("%d\n", *(int32_t*)this->data); /* cast because clang doesn't shut up about pointers */
            break;

        case PROP_STRING:
            printf("%s\n", (char*)this->data);
            break;

        case PROP_PTR:
        case PROP_RAW:
            for (i = 0; i < this->size; i++)
            {
                printf("0x%x ", 0xFF & (((char*)this->data)[i]));
            }
            printf("\n");
            break;

            break;

        case PROP_ANY:
            printf("TODO: not handled!\n");
            break;
    }
    printf("\n");
}

int32_t Property::getSize(void)
{
    return this->size;
}
