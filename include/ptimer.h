#ifndef NASHBE_PTIMER_H
#define NASHBE_PTIMER_H

#include "port.h"
#include <assert.h>

#ifdef __cplusplus__
extern "C"{
#endif

#if PORT_SYS_OS == SYS_OS_WIN32 || PORT_SYS_OS == SYS_OS_WIN64
    #include <profileapi.h>
    #define PTIMER_TYPE LARGE_INTEGER*
    #define PTIMER_START(x) PTIMER_TYPE _end; PTIMER_TYPE _freq; \
        assert(QueryPerformanceFrequency(_freq));\
        assert(QueryPerformanceCounter(x))
    #define PTIMER_STOP(x) QueryPerformanceCounter(_end);\
        x->QuadPart -= _end->QuadPart
    #define PTIMER_ELAPSED(x) (double)(x->QuadPart)/_freq->QuadPart
#elif PORT_SYS_OS == SYS_OS_MACOSX
    #include <mach/mach_time.h>
    #define PTIMER_TYPE uint64_t
    extern double _ptimer_mac_scale(PTIMER_TYPE);
    #define PTIMER_START(x) PTIMER_TYPE _end; x = mach_absolute_time()
    #define PTIMER_STOP(x) _end = mach_absolute_time(); x = _end - x;
    #define PTIMER_ELAPSED(x) _ptimer_mac_scale(x)
#else
    #error Could not obtain timers for your system.
#endif

#ifdef __cplusplus__
}
#endif

#endif