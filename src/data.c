#include "data.h"
#include "ptimer.h"
#include <stddef.h>
#include <assert.h>


data_variable_head_t* help_create_var_head(mm_char_t const* label, data_measure_type_enum type)
{
    /*
        This helper function creates variable heads for
        the construction of independent and dependent
        variables.

        #PRECONDITION:

        #POSTCONDITION:
            Assuming the preconditions are met, the function
            will produce a data variable head with the
            specified label and measurement type.
    */
    assert(label != NULL);
    data_variable_head_t* ret_head = malloc(sizeof(data_variable_head_t));
    assert(ret_head != NULL);
    ret_head->label = create_string(label);
    assert(ret_head->label != NULL);
    ret_head->measure = type;
    return ret_head;
}

data_independent_t* help_create_indep_var(data_variable_head_t* head, mm_dpfloat_t* data, mm_uint_t count)
{
    /*
        This helper function produces an independent variable
        for use in a test structure.

        #PRECONDITION:
        #POSTCONDITION:
            Assuming the preconditions are met, the function
            will produce an independent variable with
            the specified label, measurement type, and
            a copy of the independent variable entries.
        #NOTE:
            The independent variable data type does
            not hold the data count. This count must
            be stored in the test struct enclosing it.
    */
    assert(count > 0 && data != NULL && head != NULL);
    data_independent_t* ret_indep = malloc(sizeof(data_independent_t));
    assert(ret_indep != NULL);
    ret_indep->metadata = head;
    ret_indep->values = malloc(sizeof(mm_dpfloat_t) * count);
    assert(ret_indep->values != NULL);
    memcpy(ret_indep->values, data, count);
    /*
    for (mm_uint_t i = 0; i < count; i++)
    {
        ret_indep->values[i] = data[i];
    }
    return ret_indep;
    */
}

data_dependent_t* help_create_dep_var(data_variable_head_t* head, mm_uint_t count_avg, mm_uint_t count_samp)
{
    /*
        This helper function creates a dependent variable
        prepared for recording test values

        #PRECONDITION:
        #POSTCONDITION:
            d
        #NOTE:
            Like the independent variable type, dependent
            variables do not have sample count or averaged
            value count stored for these counts are stored
            in the enclosing test struct.

            sample values are uninitialized when the struct
            is returned. Do not read values unless a test
            has been performed.
    */

    assert(head != NULL && count_avg > 0 && count_samp > 0);
    data_dependent_t* ret_dep = malloc(sizeof(data_dependent_t));
    assert(ret_dep != NULL);
    ret_dep->metadata = head;
    ret_dep->samples = malloc(sizeof(mm_dpfloat_t) * count_samp * count_avg);
    assert(ret_dep->samples != NULL);
    ret_dep->averages = malloc(sizeof(mm_dpfloat_t)*count_avg);
    assert(ret_dep->averages != NULL);
    return ret_dep;
}

data_struct_accesses_t* help_create_dst_array(mm_char_t const* name, int stride, int size, void* data, mm_int_t count)
{
    /*
        This helper function creates a representation for
        an array data structure to be used by the test
        struct.

        #PRECONDITION:
        #POSTCONDITION:
            Assuming the preconditions are met, this function
            will return a data structure defining an array
            with the name, stride, size, count, and memory
            address of a copy of the array.
    */

    assert(name != NULL && stride > 0 && size > 0 && data != NULL && count > 0);
    assert(stride >= size);
    mm_uint_t total_bytes = (size + size - stride)*count;
    data_struct_accesses_t* ret_dst = malloc(sizeof(data_struct_accesses_t));
    assert(ret_dst != NULL);
    ret_dst->name = create_string(name);
    ret_dst->is_array = true;
    ret_dst->size = size;
    ret_dst->stride = stride;
    ret_dst->indexes = NULL;
    ret_dst->num_index = count;
    ret_dst->data = malloc(total_bytes);
    memcpy(ret_dst->data, data, total_bytes);
}

data_struct_accesses_t* help_create_dst_other()
{

}

data_test_t* create_test(data_test_enum test_type, data_avg_method_enum avg_method)
{
    data_test_t* test = NULL;
    test = malloc(sizeof(data_test_t));
    assert(test != NULL);
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

bool provide_data_to_test(data_test_t* test, data_struct_accesses_t* dst_data)
{
    if (test != NULL)
    {
        if (dst_data->is_array)
        {
            test->data.dst_values = dst_data;
            test->metadata.num_test_points = dst_data->num_index;
        }
        else
        {
            
        }
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

void record_cache_miss()    // ignores sample_count, must rely on timer error calculation
{
    /*
        Because cache is established after memory is requested (assuming no switches),
        cache misses cannot be accurately recorded on multiple access attempts to the
        same location. For this reason, only one sample should be taken with error
        calculated separately.

        To improve the chance of recording accurate data, avoid launching other applications
        and use an array/data structure with many entries.
    */
}

void record_cache_hit() // assumes cache establishes memory, can't be used for dynamic data collection
{
    /*
        
    */
}