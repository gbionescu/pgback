#ifndef QSDK_IF_H_
#define QSDK_IF_H_
#include <stdint.h>

#define QSDK_MR_IDENTIFIER "/mem_region"
#define QSDK_DEVICE_OFFS   "/device_offset"
#define QSDK_DEVICE_SIZE   "/device_size"
#define QSDK_DEVICE_HMEM   "/device_host_mem"
#define QSDK_PAYLOAD_IDENT "/init_payload"

typedef void * mem_region;
typedef struct Device Device;

typedef struct dev_init_
{
    char * name;
    void * init_data;
    void * (*dev_init)(void * dev, void * init_data);
    void (*dev_inst)(void * dev, void * opaque);
    void (*dev_delete)(void * dev, void * opaque);
} dev_init_t;

#ifdef __cplusplus
extern "C" {
#endif

mem_region alloc_memory_region(void);

void qsdk_set_mr(Device * dev, void * mr);
void * qsdk_get_mr(Device * dev);

void instantiate_devices(void);
void instantiate_device(Device * dev);

void set_io_operations(
        void * dev,
        uint64_t (*read)(void * opaque, int64_t addr, unsigned size),
        void (*write)(void *opaque, int64_t addr, uint64_t data, unsigned size),
        int size);

mem_region * get_sysmem();

Device * create_device(const char * name, const char * type);
void map_device_to_memory(Device * dev, mem_region mr, uint64_t offset, uint64_t size);

void map_to_targetmem(mem_region * targetmem, mem_region * region, int64_t offset);

void register_board(dev_init_t * dev_info);
void register_device(dev_init_t * dev_info);

int32_t get_property_int32(Device * dev, const char * name);
void    set_property_int32(Device * dev, const char * name, int32_t value);

char * get_property_string(Device * dev, const char * name);
void   set_property_string(Device * dev, const char * name, const char * value);

void * get_property_raw(Device * dev, const char * name);
void   set_property_raw(Device * dev, const char * name, uint32_t size, void * data);

void * get_property_ptr(Device * dev, const char * name);
void   set_property_ptr(Device * dev, const char * name, void * ptr);

uint32_t get_property_size(Device * dev, const char * name);

#ifdef __cplusplus
}
#endif

#endif
