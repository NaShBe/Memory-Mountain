#include "include/sysinfo.h"
#include "include/port.h"
#include "include/types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

sys_data_t* get_data_sys()
{
    return NULL;
}

static void _perf_data_sys_coll(sys_data_t** _data)
{
    return;
}

static void _perf_help_cpu_coll(sys_data_t* data)
{
    assert(data != NULL);

    #if PORT_SYS_ARCH == SYS_ARCH_X86 || PORT_SYS_ARCH == SYS_ARCH_X86_64
        #include "include/cpuidinterp.h"
    #endif
    data;
    return;
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
