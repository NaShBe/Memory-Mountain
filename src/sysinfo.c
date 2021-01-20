#include "include/sysinfo.h"
#include "include/port.h"
#include "include/types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

data_sys_t* get_data_sys()
{
    return NULL;
}

void fill_data_sys(data_sys_t** data)
{
    return;
}

static void _perf_data_sys_coll(data_sys_t** _data)
{
    
}

static void _perf_help_cpu_coll(data_sys_t* data)
{
    assert(data != NULL);

    #if PORT_SYS_ARCH == SYS_ARCH_X86 || PORT_SYS_ARCH == SYS_ARCH_X86_64 
        #include "include/cpuidinterp.h"
        #define cpuid_param(x, y, z) assert (z >= CPUIDEAX_HIGHEST_FUNCT && z <= highest_param); \
            y = z; __cpuid(x, y)
        int registers[4];
        enum reg_enum
        {
            eax,
            ebx,
            ecx,
            edx
        } reg_enum;
        __cpuid(registers, CPUIDEAX_HIGHEST_FUNCT);
        int highest_param = registers[0];
        int leaf;

        mm_strltr_t const vendor_str[] = 
        {
            "AMDisbetter!", "AuthenticAMD", "Centaurhuals", "CyrixInstead",
            "GenuineIntel", "TransmetaCPU", "GenuineTMx68", "Geode by NSC",
            "NexGenDriven", "RiseRiseRise", "Sis Sis Sis ", "UMC UMC UMC ",
            "VIA VIA VIA ", "Vortex86 SoC", "  Shanghai  ", "HygonGenuine",
            "E2K MACHINE", "GenuineAO486", "bhyve bhyve ", " KVMKVMKVM ",
            "TCGTCGTCGTCG", "Microsoft Hv", " lrpepyh Hv ", "VMwareVMware",
            "XenVMMXenVMM", "ACRNACRNACRN", " QNXQVMBSQG ", "VirtualApple"
        };
        
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

        if (highest_param >= CPUIDEAX_PROCESSORSTR3)
        {
            int brand_string[12] = 0;
            cpuid_param(brand_string+0, leaf, CPUIDEAX_PROCESSORSTR1);
            cpuid_param(brand_string+4, leaf, CPUIDEAX_PROCESSORSTR2);
            cpuid_param(brand_string+8, leaf, CPUIDEAX_PROCESSORSTR3);
            write_to_string(brand_string, data->sys_cpu_brand_str);
        }
        else
        {
            
        }
    #else
        #error There is no data collection implementation for your current OS.
    #endif
}

static void _perf_help_sysctl_str(int* info, size_t size, char** str, size_t* strlen, int name)
{
    assert(info != NULL && str != NULL && *str == NULL);
    sysctl(info, size, NULL, strlen, NULL, 0);
    *str = malloc(*strlen);
    sysctl(info, size, *str, strlen, NULL, 0);
    return;
}

static void _perf_help_sysctl_int(int* info, size_t size, void* val, size_t valsize, int name)
{
    assert(info != NULL && val != NULL);
}