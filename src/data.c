#include "data.h"
#include "ptimer.h"
#include <stddef.h>
#include <assert.h>


data_test_t* create_test(data_test_enum test_type, data_avg_method_enum avg_method)
{
    data_test_t* test = NULL;
    test = malloc(sizeof(data_test_t));
    if (test != NULL)
    {
        test->metadata.test_type = test_type;
        test->metadata.sample_count = 0;
        test->metadata.num_test_points = 0;
        test->metadata.avg_method = avg_method;
        test->data.dst_values = NULL;
        test->data.x_ind = NULL;
        test->data.y_ind = NULL;
        test->data.dependent = NULL;
        return test;
    }
    return NULL;
}

bool provide_data_to_test(data_test_t* test, int arr_len, int* array, data_struct_accesses_t* dst_data)
{
    if (test != NULL)
    {
        

    }
    return false;
}

void perform_test(data_test_t* test)
{
    assert(test != NULL);
    if (test->metadata.test_type != test_data_structure)
    {
        register char* const restrict data_reg_retrival;    // to most accurately measure time, offsets are calculated from register instead of retrieving the value from memory every time

    }
    else
    {
        register char* restrict data_reg_retrival;
    }

}

