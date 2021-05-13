#ifndef NASHBE_STATVIEW_H
#define NASHBE_STATVIEW_H

#ifdef __cplusplus__
extern "C"{
#endif

#include "data.h"

typedef enum stat_memory_units_enum // unit to represent memory-based variable data as
{
    memory_units_bytes,         // Bytes (B):       default memory unit
    memory_units_kilobytes,     // Kilobyte (KB):   1000 Bytes
    memory_units_megabytes,     // Megabyte (MB):   1,000,000 Bytes
    memory_units_gigabytes,     // Gigabyte (GB):   1,000,000,000 Bytes
    memory_units_kibibytes,     // Kibibytes (KiB): 1024 Bytes          (2^10 B)
    memory_units_mebibytes,     // Mebibytes (MiB): 1,048,576 Bytes     (2^20 B) (1024^2 KiB)
    memory_units_gibibytes      // Gibibytes (GiB): 1,073,741,824 Bytes (2^30 B) (1024^3 KiB)
} stat_memory_units_enum;

typedef enum stat_time_units_enum   // unit to represent time-based variable data as
{
    time_units_nanoseconds,     // Nanosecond (ns):             default time unit
    time_units_microsecond,     // Microsecond (us/U+03BC):     1000 Nanoseconds
    time_units_miliseconds,     // Milisecond (ms):             1e+6 Nanoseconds    (1000 us)
    time_units_seconds,         // Second (s):                  1e+9 Nanoseconds    (1000 ms)
    time_units_minutes,         // Minutes (min):               6e+10 Nanoseconds   (60 s)
    time_units_hours            // Hour (h):                    3.6e12 Nanoseconds  (60 m)
} stat_time_units_enum;

typedef struct statview_t      // relates test and system information for use in interface
{
    struct
    {
        data_test_t*    assoc_test;     // test in current context
        sys_data_t*     assoc_sys;      // system which test was taken on
    } associates;
    struct
    {
        stat_memory_units_enum  x_ind_units;            // units for the first independent variable
        stat_memory_units_enum  y_ind_units;            // units for the second independent variable if applicable
        stat_memory_units_enum  depend_num_units;       // memory units for readthroughput (measured in [memory]/time)
        stat_time_units_enum    depend_denom_units;     // time units for readthroughput (measured in memory/[time])
    } units;
    struct 
    {
        mm_uint_t start;
        mm_uint_t end;
        mm_uint_t skip;
    } axis_x, axis_y, axis_z;   // x and y correspond to the independent variables, axis z is the dependent variable
} statview_t;

#ifdef __cplusplus__
}
#endif

#endif