#ifndef NASHBE_DATA_H
#define NASHBE_DATA_H

#ifdef __cplusplus__
extern "C"{
#endif

#include "sysinfo.h"

typedef enum data_measure_type_enum // type of measurement used for an independent or dependent variable
{
    count,      // number of something, generally countable but unitless measurement
    memory,     // measuring memory, tied to data_memory_units_enum
    time        // measuring time, tied to data_time_units_enum
}
data_measure_type_enum;

typedef enum data_memory_units_enum // unit to represent memory-based variable data as
{
    memory_units_bytes,         // Bytes (B):       default memory unit
    memory_units_kilobytes,     // Kilobyte (KB):   1000 Bytes
    memory_units_megabytes,     // Megabyte (MB):   1,000,000 Bytes
    memory_units_gigabytes,     // Gigabyte (GB):   1,000,000,000 Bytes
    memory_units_kibibytes,     // Kibibytes (KiB): 1024 Bytes          (2^10 B)
    memory_units_mebibytes,     // Mebibytes (MiB): 1,048,576 Bytes     (2^20 B) (1024^2 KiB)
    memory_units_gibibytes      // Gibibytes (GiB): 1,073,741,824 Bytes (2^30 B) (1024^3 KiB)
} data_memory_units_enum;

typedef enum data_time_units_enum   // unit to represent time-based variable data as
{
    time_units_nanoseconds,     // Nanosecond (ns):             default time unit
    time_units_microsecond,     // Microsecond (us/U+03BC):     1000 Nanoseconds
    time_units_miliseconds,     // Milisecond (ms):             1e+6 Nanoseconds    (1000 us)
    time_units_seconds,         // Second (s):                  1e+9 Nanoseconds    (1000 ms)
    time_units_minutes,         // Minutes (min):               6e+10 Nanoseconds   (60 s)
    time_units_hours            // Hour (h):                    3.6e12 Nanoseconds  (60 m)
} data_time_units_enum;

typedef enum data_test_enum             // type of test
{
    test_size_stride_throughput,     // standard test, 3D test relating array element stride and size to memory readthroughput
    test_stride_readthroughput,      // 2D test relating array element stride to readthroughput assuming constant element size
    test_size_throughput,            // 2D test relating array element size to readthroughput assuming constant element stride
    test_data_structure              // 2D test relating dynamic accesses of a data structure to readthroughput
} data_test_enum;

typedef enum data_avg_method_enum       // method to use for averaging samples per test point
{
    avg_method_mean,                    // take the mean of the samples
    avg_method_median,                  // take the median of the samples 
    avg_method_mode                     // take the mode of the samples
} data_avg_method_enum;

typedef struct data_struct_accesses_t   // accesses used for data structure test
{
    mm_string_t*    name;           // data structure name, used mainly for graph labeling
    unsigned int    num_index;      // indexes count
    void*           indexes[];      // indexes which are accessed, set to null if data structure is accessed dynamically
} data_struct_accesses_t;

typedef struct data_variable_t      // represents a variable (either independent or dependent) in a test
{
    mm_string_t             label;      // name of variable, used when labeling axis on graph
    mm_dpfloat_t*           values;     // data collected, count determined by data_test_t struct
    data_measure_type_enum  measure;    // type of measurement
} data_variable_t;

typedef struct data_test_t      // holds test data for use in graphing
{
    struct
    {
        data_test_enum          test_type;
        const mm_uint_t         test_points;
        const mm_uint_t         sample_count;
        data_avg_method_enum    avg_method;
    } metadata;

    struct
    {
        data_struct_accesses_t* values;
        data_variable_t*        x_ind;
        data_variable_t*        y_ind;
        data_variable_t*        dependent;
    } data;
} data_test_t;

typedef struct data_view_t      // relates test and system information for use in interface
{
    struct
    {
        data_test_t*    assoc_test;     // test in current context
        sys_data_t*     assoc_sys;      // system which test was taken with
    } associates;
    struct
    {
        data_memory_units_enum  x_ind_units;            // units for the first independent variable
        data_memory_units_enum  y_ind_units;            // units for the second independent variable if applicable
        data_memory_units_enum  depend_num_units;       // memory units for readthroughput (measured in [memory]/time)
        data_time_units_enum    depend_denom_units;     // time units for readthroughput (measured in memory/[time])
    } units;
    struct 
    {
        mm_uint_t start;
        mm_uint_t end;
        mm_uint_t skip;
    } axis_x, axis_y, axis_z;   // x and y correspond to the independent variables, axis z is the dependent variable
} data_view_t;

#ifdef __cplusplus__
}
#endif

#endif
