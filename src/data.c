#include "include/data.h"
#include "ptimer.h"
#include <assert.h>
#include <stdbool.h>

data_string_t* const mem_metric_str[6] = {"Bytes","Kilobytes","Megabytes","Gigabytes","Terabytes","Petabytes"};
data_string_t* const time_metric_str[5] = {"Second", "Milisecond", "Microsecond", "Nanosecond", "System Clock Tick"};

inline static void _metrics_set_labels(data_chart_t*);
inline static int _metrics_get_unit_enum(int, bool);

data_datacollect_t* create_dynm_datacollect(data_uint_t sample_count, data_uint_t depend_count, data_size_t* array_sizes, data_size_t* strides)
{
    assert(sample_count > 0 && depend_count > 0);
    assert(array_sizes != NULL && strides != NULL);
    data_datacollect_t* ret_datacoll = malloc(sizeof(data_datacollect_t));
    if (ret_datacoll == NULL)
    {
        return NULL;
    }
    ret_datacoll->coll_set_count = sample_count;
    ret_datacoll->coll_data = malloc((sizeof(data_dataset_t) + sizeof(data_real_t) * depend_count) * sample_count);
    
    if (ret_datacoll->coll_data == NULL)
    {
        free(ret_datacoll);
        return NULL;
    }

    for (int i = 0; i < sample_count; i++)
    {
        ret_datacoll->coll_data[i].set_arr_size = array_sizes[i];
        ret_datacoll->coll_data[i].set_elem_stride = strides[i];
    }
    return ret_datacoll;
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
                for (register int i = 0; i < data_arr_count; i+=data->coll_data[itr].set_elem_stride)
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
                for (register int i = 0; i < data_arr_count; i+=data->coll_data[itr].set_elem_stride)
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

data_chart_t* create_dynm_chart(data_datacollect_t* data, data_chartdetails_t met, data_charptr_t label, data_label_order_enum ord)
{
    assert(data != NULL && label != NULL);
    data_chart_t* ret_graph = malloc(sizeof(data_chart_t));
    if (ret_graph == NULL)
    {
        return NULL;
    }
    ret_graph->data = data;
    ret_graph->label = label;
    ret_graph->metrics = met;
    ret_graph->order = ord;

    _metrics_set_labels(ret_graph);

    return ret_graph;
}

static int _metrics_get_unit_enum(int value, bool tmem_ftime)
{
    if (tmem_ftime)
    {
        switch(value)
        {
            case mem_units_default:
                return mem_units_bytes;
            default:
                return value;
        }
    }
    else
    {
        switch(value)
        {
            case time_units_default:
                return time_units_seconds;
            default:
                return value;
        }
    }
    
}
static void _metrics_set_labels(data_chart_t* graph)
{
    graph->x_label = mem_metric_str[_metrics_get_unit_enum(graph->metrics.size_measure.units, true)];
    graph->y_label = mem_metric_str[_metrics_get_unit_enum(graph->metrics.stride_measure.units, true)];
    graph->num_z_label = mem_metric_str[_metrics_get_unit_enum(graph->metrics.time_measure.units, true)];
    graph->den_z_label = mem_metric_str[_metrics_get_unit_enum(graph->metrics.time_measure.per_time_units, false)];
}