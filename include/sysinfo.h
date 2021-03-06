#ifndef NASHBE_SYSINFO_H
#define NASHBE_SYSINFO_H

#include "types.h"
#include <stdint.h>

#ifdef __cplusplus__
extern "C"{
#endif

typedef enum sys_cache_type_enum
{
    cache_type_L1I,
    cache_type_L1D,
    cache_type_L2,
    cache_type_L3,
    cache_type_TLB,
    cache_type_TLBD,
    cache_type_TLBI,
    cache_type_NA
} sys_cache_type_enum;

typedef enum sys_cpu_isa_enum
{
    cpu_isa_x86,
    cpu_isa_x64,
    cpu_isa_armv8,
    cpu_isa_ppc,
    cpu_isa_mips,
    cpu_isa_sparc,
    cpu_isa_riscv
} sys_cpu_isa_enum;

typedef enum sys_mem_type_enum
{
    mem_type_SRAM,
    mem_type_DRAM,
    mem_type_SDRAM,
    mem_type_SDRSDRAM,
    mem_type_DDRSDRAM,
    mem_type_DDR2,
    mem_type_DDR3,
    mem_type_DDR4,
    mem_type_NA
} sys_mem_type_enum;

typedef struct sys_cache_body_t
{
    mm_uint_t   cache_line_size;
    mm_uint_t   cache_associativity;
    mm_uint_t   cache_sector_lines;
} sys_cache_body_t, *sys_cache_bodyptr_t;

typedef struct sys_cache_t
{
    sys_cache_type_enum type;
    mm_uint_t       cache_size;
    sys_cache_bodyptr_t  details;
} sys_cache_t, *sys_cacheptr_t;

typedef struct sys_data_t
{
    mm_string_t     sys_model_name;
    mm_string_t     sys_os_type;
    mm_string_t     sys_os_vers;
    
    mm_string_t     sys_cpu_brand_str;
    mm_uint_t       sys_cpu_count;      
    mm_uint_t       sys_cpu_frequency;  // this is in hertz

    sys_mem_type_enum   sys_mem_type;
    mm_uint_t       sys_mem_size;       // this is in bytes

    mm_uint_t       sys_cache_num;
    sys_cacheptr_t sys_cache;
} sys_data_t, *sys_dataptr_t;

extern sys_dataptr_t    get_data_sys();

#ifdef __cplusplus__
}
#endif

#endif // sysinfo.h
