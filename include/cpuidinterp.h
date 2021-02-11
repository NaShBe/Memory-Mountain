#ifndef NASHBE_CPUIDINTERP_H
#define NASHBE_CPUIDINTERP_H

#include "types.h"
#include "sysinfo.h"
#if PORT_SYS_COMP == SYS_COMP_MSVC
#include <intrin.h>
#elif PORT_SYS_COMP == SYS_COMP_GCC || PORT_SYS_COMP == SYS_COMP_CLANG
#include <cpuid.h>
#endif

// leaf values for CPUID
#define CPUIDEAX_HIGHEST_FUNCT  0x80000000
#define CPUIDEAX_PROCESSORINFO  0x80000001
#define CPUIDEAX_PROCESSORSTR1  0x80000002
#define CPUIDEAX_PROCESSORSTR2  0x80000003
#define CPUIDEAX_PROCESSORSTR3  0x80000004
#define CPUIDEAX_L1CACHE_TLBID  0x80000005
#define CPUIDEAX_L2CACHE_EXTFE  0x80000006
#define CPUIDEAX_ADVPOWERMANAG  0x80000007
#define CPUIDEAX_VIRTUALMEMSIZ  0x80000008

#define CPUIDEAX_MANUFACTUREID  0X0
#define CPUIDEAX_PROCESSORINFO  0X1
#define CPUIDEAX_CACHE_TLBDESC  0X2
#define CPUIDEAX_PROCESSORSERL  0X3
#define CPUIDEAX_CORE_CACHETOP  0X4
#define CPUIDEAX_THERMALPOWERM  0X6


#ifdef __cplusplus__
extern "C"{
#endif

extern void         cpuid_init();
extern void         cpuid_get_manufacturer_str(mm_stringptr_t);
extern void         cpuid_get_brandstring(mm_stringptr_t);
extern void         cpuid_get_logical_cores(mm_uint_t*);
extern void         cpuid_get_physical_cores(mm_uint_t*);
extern void         cpuid_get_cache_l1_details(cache_infoptr_t);
extern void         cpuid_get_cache_l2_details(cache_infoptr_t);
extern void         cpuid_get_cache_l3_details(cache_infoptr_t);

#ifdef __cplusplus__
}
#endif

#endif
