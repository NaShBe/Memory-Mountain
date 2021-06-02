#ifndef NASHBE_DATA_H
#define NASHBE_DATA_H

#ifdef __cplusplus__
extern "C"{
#endif

#include "sysinfo.h"

typedef enum data_measure_type_enum // type of measurement used for an independent or dependent variable
{
    count,      // number of something, e.g. for counting memory accesses
    memory,     // measuring memory, corresponds to stat_memory_units_enum
    time        // measuring time, corresponds to stat_time_units_enum
}
data_measure_type_enum;

typedef enum data_test_enum          // type of test
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

typedef struct data_variable_head_t     // represents metadata for variable (either independent or dependent) in a test
{
    mm_string_t             label;      // name of variable, used when labeling axis on graph
    data_measure_type_enum  measure;    // type of measurement
} data_variable_head_t;

typedef struct data_independent_t
{
    data_variable_head_t    metadata;   // data pertaining to the independent variable
    mm_dpfloat_t*           values;     // data collected, count determined by data_test_t struct
} data_independent_t;

typedef struct data_dependent_t
{
    data_variable_head_t    metadata;   // data pertaining to the dependent variable
    mm_dpfloat_t*           averages;   // value calculated based on data_avg_method_enum
    mm_dpfloat_t*           samples;    // test values, grouped to calculate averages
} data_dependent_t;

typedef struct data_test_t      // holds all data for a test
{
    struct
    {
        data_test_enum          test_type;
        mm_uint_t               num_test_points;
        mm_uint_t               sample_count;
        data_avg_method_enum    avg_method;
    } metadata;
    struct
    {
        data_struct_accesses_t* dst_values;
        data_independent_t*     x_ind;
        data_independent_t*     y_ind;
        data_dependent_t*       dependent;
    } data;
} data_test_t;

#ifdef __cplusplus__
}
#endif

#endif
