#include "include/sysinfo.h"
#include <stdlib.h>
#include <assert.h>

static const data_sys_t _null_data_sys = {NULL, 0, NULL, 0, NULL, 0, NULL, 0, 0, 0, 0.0, 0, NULL};
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
    #if defined(__APPLE__) && defined(__MACH__)
        #include <sys/sysctl.h>
        #if defined (_SYS_SYSCTL_H_)
            #define SYSCTL_QUEUE_COUNT 2
            #define SYSCTL_CTL_FLAG 0
            #define SYSCTL_CTL_VAR 1
            int sysctl_queue[SYSCTL_QUEUE_COUNT] = {CTL_HW, 0};
            **_data = _null_data_sys;
            _perf_help_sysctl_str(sysctl_queue, SYSCTL_QUEUE_COUNT, (*_data)->sys_cpu_name, &(*_data)->sys_cpu_name_len, HW_MACHINE);
            _perf_help_sysctl_str(sysctl_queue, SYSCTL_QUEUE_COUNT, (*_data)->sys_model_name, &(*_data)->sys_model_name_len, HW_MODEL);
            _perf_help_sysctl_int(sysctl_queue, SYSCTL_QUEUE_COUNT, (*_data)->sys_mem_size, sizeof((*_data)->sys_mem_size), HW_MEMSIZE);
            _perf_help_sysctl_int(sysctl_queue, SYSCTL_QUEUE_COUNT, (*_data)->sys_cpu_count, sizeof((*_data)->sys_cpu_count), HW_NCPU);
            _perf_help_sysctl_int(sysctl_queue, SYSCTL_QUEUE_COUNT, (*_data)->sys_cpu_frequency, sizeof((*_data)->sys_cpu_frequency), HW_CPU_FREQ);
            sysctl_queue[SYSCTL_CTL_FLAG] = CTL_KERN;
            _perf_help_sysctl_str(sysctl_queue, SYSCTL_QUEUE_COUNT, (*_data)->sys_os_type, &(*_data)->sys_os_type_len, KERN_OSTYPE);
            _perf_help_sysctl_str(sysctl_queue, SYSCTL_QUEUE_COUNT, (*_data)->sys_os_vers, &(*_data)->sys_os_vers_len, KERN_OSRELEASE);

        #else
            #include <unistd.h>
            
        #endif
    #elif defined(_WIN32)
        #include <windows.h>
        SYSTEM_INFO sys_info;
        #ifdef _WIN64
            GetSystemInfo(sys_info);
        #else
            GetNativeSystemInfo(sys_info);
        #endif
        
    #else
        #error There's no implementation for data collection of your current OS.
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