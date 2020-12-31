#ifndef NASHBE_SYSINFO_H
#define NASHBE_SYSINFO_H

#include <stdint.h>

#ifdef __cplusplus__
extern "C"{
#endif

typedef enum cache_type_enum
{
    cache_type_L1I,
    cache_type_L1D,
    cache_type_L2,
    cache_type_L3,
    cache_type_NA
} cache_type_enum;

typedef struct cache_info
{
    cache_type_enum type;
    uintptr_t       cache_size;
} cache_info;

typedef struct data_sys_t
{
    char*       sys_model_name;
    size_t      sys_model_name_len;
    char*       sys_os_type;
    size_t      sys_os_type_len;
    char*       sys_os_vers;
    size_t      sys_os_vers_len;
    char*       sys_cpu_name;
    size_t      sys_cpu_name_len;

    uintptr_t   sys_mem_size;       // this is in bytes
    uint8_t     sys_cpu_count;      
    uint64_t    sys_cpu_frequency;  // this is in hertz

    uint8_t     sys_cache_num;
    cache_info* sys_cache;
} data_sys_t;

extern data_sys_t*  get_data_sys();
extern void         fill_data_sys(data_sys_t**);


#ifdef __cplusplus__
}
#endif

#endif // sysinfo.h
