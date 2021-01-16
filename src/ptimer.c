#include "include/ptimer.h"


#if PORT_SYS_OS == SYS_OS_MACOSX
static PTIMER_TYPE _ptimer_mac_precision_scale(PTIMER_TYPE elapsed_time)
{
    mach_timebase_info_data_t time_measure;     // stores how time is represented on MacOSX in nanoseconds
    assert(mach_timebase_info(&time_measure) == KERN_SUCCESS);
    PTIMER_TYPE high_bits = (elapsed_time >> 32) * time_measure.numer;
    PTIMER_TYPE low_bits = (elapsed_time & 0xFFFFFFFFull) * time_measure.numer;
    PTIMER_TYPE high_remaind = (high_bits % time_measure.denom) << 32;
    high_bits/=time_measure.denom;
    low_bits/=time_measure.denom;
    high_remaind/=time_measure.denom;   
    return (high_bits << 32) + high_remaind + low_bits;
}
double _ptimer_mac_scale(PTIMER_TYPE elapsed_time)
{
    return 1e-9 * _ptimer_mac_precision_scale(elapsed_time);
}
#endif
