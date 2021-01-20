#ifndef NASHBE_SYSINFO_H
#define NASHBE_SYSINFO_H

#include "types.h"
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
    cache_type_TLB,
    cache_type_TLBD,
    cache_type_TLBI,
    cache_type_NA
} cache_type_enum;

typedef enum cpu_isa_enum
{
    x86,
    x64,
    armv8,
    ppc,
    mips,
    sparc,
    riscv
} cpu_isa_enum;

typedef struct cache_details_t
{
    mm_uint_t   cache_line_size;
    mm_uint_t   cache_associativity;
    mm_uint_t   cache_sector_lines;
} cache_details_t, *cache_detptr_t;

typedef struct cache_info_t
{
    cache_type_enum type;
    mm_uint_t       cache_size;
    cache_detptr_t  details;
} cache_info_t, *cache_infoptr_t;


typedef struct data_sys_t
{
    mm_string_t     sys_model_name;
    mm_string_t     sys_os_type;
    mm_string_t     sys_os_vers;
    mm_string_t     sys_cpu_brand_str;

    mm_uint_t       sys_mem_size;       // this is in bytes
    mm_uint_t       sys_cpu_count;      
    mm_uint_t       sys_cpu_frequency;  // this is in hertz

    mm_uint_t       sys_cache_num;
    cache_infoptr_t sys_cache;
} data_sys_t;

extern data_sys_t*  get_data_sys();
extern void         fill_data_sys(data_sys_t**);


#ifdef __cplusplus__
}
#endif

#endif // sysinfo.h
