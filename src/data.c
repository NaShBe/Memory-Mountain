#include "data.h"
#include "ptimer.h"
#include <stddef.h>
#include <assert.h>


data_test_t* develop_test(data_test_enum test_type)
{
    return NULL;
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

