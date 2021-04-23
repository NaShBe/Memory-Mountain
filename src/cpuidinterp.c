#include "include/cpuidinterp.h"
#include "string.h"

// Define a macro for portable use of __cpuid (currently produces errors in macos)

static mm_strltr_t const vendor_str[] = 
{
    "AMDisbetter!", "AuthenticAMD", "Centaurhuals", "CyrixInstead",
    "GenuineIntel", "TransmetaCPU", "GenuineTMx68", "Geode by NSC",
    "NexGenDriven", "RiseRiseRise", "Sis Sis Sis ", "UMC UMC UMC ",
    "VIA VIA VIA ", "Vortex86 SoC", "  Shanghai  ", "HygonGenuine",
    "E2K MACHINE", "GenuineAO486", "bhyve bhyve ", " KVMKVMKVM ",
    "TCGTCGTCGTCG", "Microsoft Hv", " lrpepyh Hv ", "VMwareVMware",
    "XenVMMXenVMM", "ACRNACRNACRN", " QNXQVMBSQG ", "VirtualApple"
};

static mm_strltr_t const manufact_str[] =
{
    "Intel", "AMD", "Transmeta", "Cyrix"
};

static mm_int_t highest_param_basic;
static mm_int_t highest_param_extended;

static mm_int_t registers[4];
static enum reg_enum
{
    eax,
    ebx,
    ecx,
    edx
} reg_enum;

void cpuid_init()
{
    __cpuid(registers, CPUIDEAX_HIGHEST_FUNCT);
    highest_param_extended = registers[eax];
    __cpuid(registers, CPUIDEAX_MANUFACTUREID);
    highest_param_basic = registers[eax];
}

void cpuid_get_manufacturer_str(mm_stringptr_t str)
{
    __cpuid(registers, CPUIDEAX_MANUFACTUREID);
}

void cpuid_get_brandstring(mm_stringptr_t str)
{
    if (highest_param_extended >= CPUIDEAX_PROCESSORSTR3)
    {
        int brand_string[12];
        __cpuid(registers, CPUIDEAX_PROCESSORSTR1);
        memcpy(brand_string+0, registers, sizeof(int)*4);
        __cpuid(registers, CPUIDEAX_PROCESSORSTR2);
        memcpy(brand_string+4, registers, sizeof(int)*4);
        __cpuid(registers, CPUIDEAX_PROCESSORSTR3);
        memcpy(brand_string+8, registers, sizeof(int)*4);
        write_to_string(str, brand_string);
    }
}

void cpuid_get_logical_cores(mm_uint_t* num)
{

}

void cpuid_get_physical_cores(mm_uint_t* num)
{

}

void cpuid_get_cache_l1_details(sys_cacheptr_t info)
{

}

void cpuid_get_cache_l2_details(sys_cacheptr_t info)
{

}

void cpuid_get_cache_l3_details(sys_cacheptr_t info)
{

}

/*
        union sys_cpubrand
        {
            int val[4];
            mm_char_t venstr[sizeof(int) * 4];
        } sys_cpubrand;

        cpuid_param(registers, leaf, CPUIDEAX_HIGHEST_FUNCT);
        sys_cpubrand.val[0] = registers[ebx];
        sys_cpubrand.val[1] = registers[edx];
        sys_cpubrand.val[2] = registers[ecx];
        sys_cpubrand.val[3] = 0;

        if
        (
            !strcmp(sys_cpubrand.venstr, vendor_str[0]) ||
            !strcmp(sys_cpubrand.venstr, vendor_str[1])
        )
        {
            // define cpu type
            1;
        }
        cpuid_param(brand_string+0, leaf, CPUIDEAX_PROCESSORSTR1);
            cpuid_param(brand_string+4, leaf, CPUIDEAX_PROCESSORSTR2);
            cpuid_param(brand_string+8, leaf, CPUIDEAX_PROCESSORSTR3);
*/
