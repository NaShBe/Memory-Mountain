#include "include/data.h"
#include "ptimer.h"
#include <assert.h>

data_datacollect_t* create_dynm_datacollect(data_uint_t cnt, data_size_t* arr, data_size_t* strd, data_uint_t depcnt)
{

}

void collect_data(data_datacollect_t* data)
{
    assert(data != NULL);
    assert(data->coll_dep_count > 0 && data->coll_set_count > 0);
    data_uint_t data_sample_count = data->coll_set_count;
    data_uint_t itr;
    for (itr = 0; itr < data_sample_count; itr++)
    {
        const data_arr_count = data->coll_data[itr].set_arr_size;
        data_size_t data_arr_size = sizeof(data_pool_t) * data_arr_count;
        #if _USER_ACCESS_METHOD == ACCESS_METHOD_VOLATILE_ACCESS
            register const data_pool_t* const restrict data_array = malloc(data_arr_size);
            for(int j = 0; j < data->coll_dep_count; j++)
            {
                PTIMER_TYPE timer;
                PTIMER_START(timer);
                for (register int i = 0; i < data_arr_count; i++)
                {
                    /*
                        register's use here is only because it will most closely represent the time needed solely to 
                        access of the array elements, even if the rest of the code is somewhat slower because of it
                        or if the suggestion is ignored altogether.
                    */
                    data_array[i];
                }
                PTIMER_STOP(timer);
                double timer_elapsed = PTIMER_ELAPSED(timer);
            }
        #elif _USER_ACCESS_METHOD == ACCESS_METHOD_ADDITION
            register data_arrval_t* const restrict data_array = malloc(data_arr_size);
            for(int j = 0; j < data->coll_dep_count; j++)
            {
                PTIMER_TYPE timer;
                PTIMER_START(timer);
                for (register int i = 0; i < data_arr_count; i++)
                {
                    data_array[i]++;
                }
                PTIMER_STOP(timer);
                double timer_elapsed = PTIMER_ELAPSED(timer);
                data->coll_data[itr].set_read_throughput[j] = timer_elapsed;
            }
        #else
            #error _USER_ACCESS_METHOD not defined, possible error where undefined from data.h header
        #endif
        free(data_array);
    }
    return;
}

data_chart_t* create_dynm_chart(data_datacollect_t* data)
{
    return NULL;
}