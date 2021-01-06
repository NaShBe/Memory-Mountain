#ifndef NASHBE_PTIMER_H
#define NASHBE_PTIMER_H

#include "port.h"
#include <assert.h>

#ifdef __cplusplus__
extern "C"{
#endif

#if defined(SYS_OS_WIN32) || defined(SYS_OS_WIN64)
    #include <profileapi.h>
    #define PTIMER_TYPE LARGE_INTEGER*
    #define PTIMER_START(x) PTIMER_TYPE _end; PTIMER_TYPE _freq; \
        assert(QueryPerformanceFrequency(_freq));\
        assert(QueryPerformanceCounter(x))
    #define PTIMER_STOP(x) QueryPerformanceCounter(_end);\
        x->QuadPart -= _end->QuadPart
    #define PTIMER_ELAPSED(x) (double)(x->QuadPart)/_freq->QuadPart
#elif defined(SYS_OS_MACOS) || defined(SYS_OS_MACOSX)
    #include <mach/mach_time.h>
#else
#endif


#ifdef __cplusplus__
}
#endif

#endif