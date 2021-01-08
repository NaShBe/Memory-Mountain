#include "include/sysinfo.h"
#include "include/port.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

static const data_sys_t _null_data_sys = {NULL, 0, NULL, 0, NULL, 0, NULL, 0, 0, 0, 0.0, 0, NULL};
static const char str_unknown[] = "Undetermined";
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
    #if PORT_SYS_ARCH == SYS_ARCH_X86 || PORT_SYS_ARCH == SYS_ARCH_X86_64
        #if PORT_SYS_COMP == SYS_COMP_MSVC
            #include <intrin.h>
            #include <limits.h>
            int registers[4];
            int leaf;
            
            __cpuid(registers, leaf);
            
        #elif PORT_SYS_COMP == SYS_COMP_GCC || PORT_SYS_COMP == SYS_COMP_CLANG
            #include <cpuid.h>
            int registers[4];
            int* const eax = &(registers[0]);
            int* const ebx = &(registers[0]);
            int* const edx = &(registers[0]);
            int* const ecx = &(registers[0]);
            if (!(__get_cpuid(0, eax, ebx, ecx, edx)))
            {
                fprintf(stderr, " [!] __get_cpuid() produced an error");
            }
            else
            {
                
            }
        #endif
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