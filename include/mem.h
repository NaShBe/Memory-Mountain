
#ifndef NASHBE_MEM_H
#define NASHBE_MEM_H

#ifndef _USER_DATA_TYPE
#define _USER_DATA_TYPE int
#endif

#include "include/sysinfo.h"
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#ifdef __cplusplus__
extern "C"{
#endif

typedef _USER_DATA_TYPE data_arrval_t;

typedef struct data_dataset_t
{
    size_t set_elem_size;
    size_t set_elem_stride;
    double set_read_throughput[];
} data_dataset_t;

typedef struct data_datacollect_t
{
    data_sys_t coll_sys;
    uint32_t coll_set_count;
    data_dataset_t* coll_data;
} data_datacollect_t;



#ifdef __cplusplus__
}
#endif

#endif // mem.h
