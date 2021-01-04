
#ifndef NASHBE_DATA_H
#define NASHBE_DATA_H

#ifndef _USER_DATA_TYPE
#define _USER_DATA_TYPE int
#endif

#define ACCESS_METHOD_VOLATILE_ACCESS 0
#define ACCESS_METHOD_ADDITION 1
#ifndef _USER_ACCESS_METHOD
#define _USER_ACCESS_METHOD ACCESS_METHOD_ADDITION
#endif

#include "include/sysinfo.h"
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus__
extern "C"{
#endif

typedef enum data_mem_units_enum
{
    mem_units_bytes,
    mem_units_kilobytes,
    mem_units_megabytes,
    mem_units_gigabytes,
    mem_units_terabytes,
    mem_units_petabytes
} data_mem_units_enum;

typedef enum data_time_units_enum
{
    time_units_seconds,
    time_units_miliseconds,
    time_units_clock_ticks
} data_time_units_enum;

typedef enum data_label_order_enum
{
    XYZ,
    XZY,
    ZXY,
    ZYX,
    YZX,
    YXZ
} data_label_order_enum;

typedef _USER_DATA_TYPE         data_arrval_t;  // user-defined data type for array
typedef volatile data_arrval_t  data_pool_t;    // where array access is made for addition method
typedef intmax_t                data_int_t;     // represents a signed integer
typedef uintmax_t               data_uint_t;    // represents an unsigned integer
typedef double                  data_real_t;    // represents a real-number representation
typedef size_t                  data_size_t;    // represents a measure of memory space in bytes
typedef const char*             data_string_t;  // represents a safe character string
typedef char*                   data_charptr_t; // represents a standard character string

typedef struct data_dataset_t
{
    data_size_t set_arr_size;           // independent variable: array size in bytes
    data_size_t set_elem_stride;        // independent variable: array stride in bytes
    data_real_t set_read_throughput[];  // dependent variable: read throughput in bytes per second
} data_dataset_t;

typedef struct data_datacollect_t
{
    data_sys_t coll_sys;                // system information
    data_uint_t coll_set_count;         // number of data sets
    data_uint_t coll_dep_count;         // number of dependent variables
    data_dataset_t* coll_data;          // data sets
} data_datacollect_t;

typedef struct data_chartdetails_t
{
    struct size_measure
    {
        data_mem_units_enum units;
        data_int_t          start;
        data_int_t          skip;
        data_int_t          end;
    };
    struct stride_measure
    {
        data_mem_units_enum units;
        data_int_t          start;
        data_int_t          skip;
        data_int_t          end;
    };
    struct time_measure
    {
        data_mem_units_enum     units;
        data_time_units_enum    per_time_units;
        data_int_t              start;
        data_int_t              skip;
        data_int_t              end;
    };
} data_chartdetails_t;

typedef struct data_chart_t
{
    data_datacollect_t*     data;       // data associated with the chart
    data_chartdetails_t     metrics;    // chart details
    data_charptr_t          label;      // label of the chart
    data_string_t           x_label;    // label for array size
    data_string_t           y_label;    // label for stride size
    data_string_t           z_label;    // label for read throughput
    data_label_order_enum   order;      // determines the orientation of the chart
} data_chart_t;

extern data_datacollect_t* create_dynm_datacollect(data_uint_t, data_size_t*, data_size_t*, data_uint_t);
extern void collect_data(data_datacollect_t*);
extern data_chart_t* create_dynm_chart(data_datacollect_t*);

#ifdef __cplusplus__
}
#endif

#endif // data.h