#include "data.h"
#include "ptimer.h"
#include <stddef.h>
#include <assert.h>


data_variable_head_t* help_create_var_head(mm_char_t const* const label, data_measure_type_enum type)   /* creates a variable head with label and type specified */
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
    data_variable_head_t* ret_head = (data_variable_head_t*)malloc(sizeof(data_variable_head_t));
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
    data_independent_t* ret_indep = (data_independent_t*)malloc(sizeof(data_independent_t));
    assert(ret_indep != NULL);
    ret_indep->metadata = head;
    ret_indep->values = (mm_dpfloat_t*)malloc(sizeof(mm_dpfloat_t) * count);
    assert(ret_indep->values != NULL);
    memcpy(ret_indep->values, data, count);
    return ret_indep;
}

data_dependent_t* help_create_dep_var(data_variable_head_t* head) /* creates a dependent variable with the head atttached but no sample or average data initialized*/
{
    /*
        This helper function creates a dependent variable
        prepared for recording test values

        #PRECONDITION:
        #POSTCONDITION:
        #NOTE:
            Like the independent variable type, dependent
            variables do not have sample count or averaged
            value count stored for these counts are stored
            in the enclosing test struct.

            Because samples are obtained only once a reading
            is performed, sample and average data pointers are
            set to NULL to signify premature dereference.
    */

    assert(head != NULL);
    data_dependent_t* ret_dep = (data_dependent_t*)malloc(sizeof(data_dependent_t));
    assert(ret_dep != NULL);
    ret_dep->metadata = head;
    ret_dep->samples = NULL;
    ret_dep->averages = NULL;
    return ret_dep;
}

data_data_struct_t* help_create_dst_array(/*mm_char_t const* name, int stride, int size, void* data, mm_int_t count*/)
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
   return NULL;
}

data_data_struct_t* help_create_dst_other()
{

}

data_test_t* create_test(data_test_enum test_type, data_avg_method_enum avg_method)
{
    data_test_t* test = NULL;
    test = (data_test_t*)malloc(sizeof(data_test_t));
    assert(test != NULL);
    test->metadata.test_type = test_type;
    test->metadata.sample_count = 0;
    test->metadata.test_point_count = 0;
    test->metadata.avg_method = avg_method;
    test->data.dst_values = NULL;
    test->data.x_ind = NULL;
    test->data.y_ind = NULL;
    test->data.dependent = NULL;
    return test;
}

bool provide_data_to_test(data_test_t* test, data_data_struct_t* dst_data)
{

}

data_entry_t perform_generic_reading(mm_generic_t* addr[], mm_uint_t addr_count, mm_uint_t elem_size)
{

}

data_entry_t perform_array_reading(mm_generic_t* addr, mm_uint_t addr_count, mm_uint_t elem_size, mm_uint_t elem_stride)
{

}

// void perform_test(data_test_t* test)
// {
//     assert(test != NULL);
//     if (test->metadata.test_type != test_data_structure)
//     {
//         /*
//             When a test is performed, the following algorithm is performed:
//                 1) determine test type
//                     a) if the test is of an array type (i.e. not test_data_structure):
//                         i) obtain the address of the array and store it (preferably on the register)
//                         ii) for every test point, get the time required to read every byte of an element from the array
//                         iii) repeat this for the set number of samples

//                     b) if the test is of data structure type (i.e. is test_data_structure)
//                         i) obtain the adress of the index list and store it (preferably on the register)
//                         ii) for every test point, get the time required to read every byte of the addressed element
//                         iii) repeat this for the set number of samples
//         */
//         register const volatile char* const data_array = test->data.dst_values->data;    // the array data is accessed through this pointer
//         for (mm_uint_t i = 0; i < test->metadata.sample_count; i++)
//         {
//             for (mm_uint_t j = 0; j < test->metadata.test_point_count; j++)
//             {
//                 register mm_uint_t curr_index = j * test->data.dst_values->stride;
//                 PTIMER_TYPE timer;
//                 PTIMER_START(timer);
//                 // TIME SENSITIVE CODE BEGINS HERE //
//                 for (register mm_uint_t k = 0; k < test->data.dst_values->size; k++)
//                 {
//                     data_array[curr_index + k]; // each byte of every index is accessed
//                 }
//                 // TIME SENSITIVE CODE ENDS HERE //
//                 PTIMER_STOP(timer);
//                 double time_elapsed = PTIMER_ELAPSED(timer);
//                 test->data.dependent->samples[j+i] = time_elapsed;
//             }
//         }
//     }
//     else
//     {
//         register char* data_reg_retrival;
//     }

// }
