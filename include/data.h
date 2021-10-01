#ifndef NASHBE_DATA_H
#define NASHBE_DATA_H

#ifdef __cplusplus__
extern "C"{
#endif

#include "types.h"
#include "ptimer.h"

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

typedef enum data_data_struct_type_enum
{
    data_struct_general,
    data_struct_array,
    data_struct_linked_list,
    data_struct_binary_tree
} data_data_struct_type_enum, data_dst_type_enum;

typedef struct data_generic_entry_t
{
    mm_uint_t   avg_offset;
    mm_uint_t   elem_size;
    mm_uint_t   elem_count;
    PTIMER_TYPE time_elapsed;
} data_generic_entry_t;

typedef struct data_array_entry_t
{
    mm_uint_t   elem_stride;
    mm_uint_t   elem_size;
    mm_uint_t   elem_count;
    PTIMER_TYPE time_elapsed;
} data_array_entry_t;

typedef struct data_data_struct_t
{
    struct
    {
        mm_string_t*        name;
        data_dst_type_enum  dst_type;
    } metadata;

    void* data;
} data_data_struct_t, data_dst_t;

typedef struct data_array_t
{
    mm_uint_t       elem_size;
    mm_uint_t       elem_stride;
    mm_generic_t*   elements;
} data_array_t;

typedef struct data_linked_list_t
{
    mm_uint_t elem_size;
    void* (*get_next_addr)(void*);
    void* curr_node;
} data_linked_list_t;

typedef struct data_binary_tree_t
{
    mm_uint_t elem_size;
    void* (*get_left_addr)(void*);
    void* (*get_right_add)(void*);
    void* curr_node;
} data_binary_tree_t;

typedef struct data_general_t
{
    mm_uint_t elem_size;
    mm_uint_t elem_count;
    void* (*get_next_elem)(void*);
    void (*read_elem)(void*);
    void* curr_elem;
} data_general_t;


typedef struct data_variable_head_t     // represents metadata for variable (either independent or dependent) in a test
{
    mm_string_t*            label;      // name of variable, used when labeling axis on graph
    data_measure_type_enum  measure;    // type of measurement
} data_variable_head_t;

typedef struct data_independent_t
{
    data_variable_head_t*   metadata;   // data pertaining to the independent variable
    mm_dpfloat_t*           values;     // data collected, count determined by data_test_t struct
} data_independent_t;

typedef struct data_dependent_t
{
    data_variable_head_t*   metadata;   // data pertaining to the dependent variable
    mm_dpfloat_t*           averages;   // value calculated based on data_avg_method_enum
    mm_dpfloat_t*           samples;    // test values, grouped to calculate averages
} data_dependent_t;

typedef struct data_test_t      // holds all data for a test
{
    struct
    {
        data_test_enum          test_type;
        data_avg_method_enum    avg_method;
        mm_uint_t               test_point_count;
        mm_uint_t               sample_count;
    } metadata;
    struct
    {
        data_dst_t*             dst_values;
        data_independent_t*     x_ind;
        data_independent_t*     y_ind;
        data_dependent_t*       dependent;
    } data;
} data_test_t;

#ifdef __cplusplus__
}
#endif

#endif
