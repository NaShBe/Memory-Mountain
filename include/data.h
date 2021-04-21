#ifndef NASHBE_DATA_H
#define NASHBE_DATA_H

#ifdef __cplusplus__
extern "C"{
#endif

#include "sysinfo.h"
typedef enum data_measure_type_enum
{
    count,
    memory,
    time
}
data_measure_type_enum;

typedef enum data_memory_units_enum
{
    memory_units_bytes,         // default unit
    memory_units_kilobytes,
    memory_units_megabytes,
    memory_units_gigabytes,
    memory_units_kibibytes,
    memory_units_mebibytes,
    memory_units_gibibytes
} data_memory_units_enum;

typedef enum data_time_units_enum
{
    time_units_nanoseconds,     // default unit
    time_units_miliseconds,
    time_units_seconds,
    time_units_minutes,
    time_units_hours
} data_time_units_enum;

typedef enum data_test_enum
{
    measure_size_stride_throughput,
    measure_stride_readthroughput,
    measure_size_throughput,
    measure_data_structure
} data_test_enum;

typedef enum data_avg_method_enum
{
    avg_method_mean,
    avg_method_median,
    avg_method_mode
} data_avg_method_enum;

typedef struct data_struct_accesses_t
{
    mm_string_t* name;
    unsigned int num_index;
    void* indexes[];
} data_struct_accesses_t;

typedef struct data_measure_t
{
    mm_string_t label;
    mm_dpfloat_t* values;
}
data_measure_t;

typedef struct data_test_t
{
    data_test_enum measure_type;
    const mm_uint_t test_points;
    const mm_uint_t sample_count;
    data_measure_t x_ind;
    data_measure_t y_ind;
    data_measure_t dependent;
}
data_test_t;

#ifdef __cplusplus__
}
#endif

#endif
