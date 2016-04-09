#ifndef QSDK_QEMU_GATEWAY_H
#define QSDK_QEMU_GATEWAY_H

#ifdef __cplusplus
extern "C" {
#endif

extern void * get_system_memory(void);
extern void * QSDK_alloc_memory_region(void);
extern void qemu_system_reset_request(void);

extern void * cpu_arm_init(const char * cpu_model);

/* extern void qdev_init_nofail(DeviceState *dev); */
extern void qdev_init_nofail(void * dev);
extern void * get_qemu_sys_bus_device(void * device);
extern void * get_qemu_device(void * device);

extern void register_qsdk_board(const char * name);

/* void cpu_reset(CPUState *cpu); */
extern void cpu_reset(void *cpu);

/* void * memory_region_get_ram_ptr(MemoryRegion * mr); */
extern void * memory_region_get_ram_ptr(void * mr);

/* DeviceState *qdev_create(BusState *bus, const char *name); */
extern void * qdev_create(void *bus, const char *name);

/* void set_nvic(void * nvic, void * cpu); */
extern void set_nvic(void * nvic, void * cpu);

/* qemu_irq qdev_get_gpio_in(DeviceState *dev, int n); */
extern void * qdev_get_gpio_in(void *dev, int n);

/* void * init_memory_region_ops(void * readfunc, void * writefunc); */
extern void * init_memory_region_ops(void * readfunc, void * writefunc);

/* void qemu_register_reset(QEMUResetHandler *func, void *opaque); */
extern void qemu_register_reset(void *func, void *opaque);

/* void qdev_prop_set_uint32(DeviceState *dev, const char *name, uint32_t value); */
extern void qdev_prop_set_uint32(void *dev, const char *name, uint32_t value); /* TODO: qdev-properties.h */

/* void memory_region_add_subregion(MemoryRegion *mr,
                                   hwaddr offset,
                                   MemoryRegion *subregion); */
extern void memory_region_add_subregion(void *mr,
                                        uint64_t offset,
                                        void *subregion);

/* void sysbus_connect_irq(SysBusDevice *dev, int n, qemu_irq irq); */
extern void sysbus_connect_irq(void *dev, int n, void *irq);

/* void load_elf_from_disk(char * kernel_filename, int mem_size, int endian); */
extern void load_elf_from_disk(char * kernel_filename, int mem_size, int endian);

/* qemu_irq qemu_allocate_irq(qemu_irq_handler handler, void *opaque, int n); */
extern void * qemu_allocate_irq(void * handler, void *opaque, int n);

/* void qdev_connect_gpio_out_named(DeviceState *dev, const char *name, int n,
                                 qemu_irq pin); */
extern void qdev_connect_gpio_out_named(void *dev, const char *name, int n,
        void * pin);

/*
void memory_region_init_ram(MemoryRegion *mr,
                            struct Object *owner,
                            const char *name,
                            uint64_t size,
                            Error **errp); */
extern void memory_region_init_ram(void *mr,
                            void *owner,
                            const char *name,
                            uint64_t size,
                            void **errp);

/*
void memory_region_init_ram_ptr(MemoryRegion *mr,
                                struct Object *owner,
                                const char *name,
                                uint64_t size,
                                void *ptr); */
extern void memory_region_init_ram_ptr(void *mr,
                                void *owner,
                                const char *name,
                                uint64_t size,
                                void *ptr);

/*
void memory_region_init_io(MemoryRegion *mr,
                           struct Object *owner,
                           const MemoryRegionOps *ops,
                           void *opaque,
                           const char *name,
                           uint64_t size); */
extern void memory_region_init_io(void *mr,
                           void *owner,
                           void *ops,
                           void *opaque,
                           const char *name,
                           uint64_t size);

/*
void memory_region_init_alias(MemoryRegion *mr,
                              struct Object *owner,
                              const char *name,
                              MemoryRegion *orig,
                              hwaddr offset,
                              uint64_t size); */
extern void memory_region_init_alias(void *mr,
                              void *owner,
                              const char *name,
                              void *orig,
                              uint64_t offset,
                              uint64_t size);
/*
void memory_region_init_rom_device(MemoryRegion *mr,
                                   struct Object *owner,
                                   const MemoryRegionOps *ops,
                                   void *opaque,
                                   const char *name,
                                   uint64_t size,
                                   Error **errp); */
void memory_region_init_rom_device(void *mr,
                                   void *owner,
                                   void *ops,
                                   void *opaque,
                                   const char *name,
                                   uint64_t size,
                                   void **errp);


#ifdef __cplusplus
}
#endif

#endif
