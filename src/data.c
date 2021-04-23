#include "data.h"
#include <cstddef>


data_test_t* develop_test(data_test_enum test_type)
{
    return NULL;
}

void perform_test(data_test_t* test)
{
    if (test->metadata.test_type != test_data_structure)
    {
        register char* const restrict data_reg_retrival;    // to most accurately measure time, offsets are calculated from register instead of retrieving the value from memory every time
    }
    else
    {
         register char* restrict data_reg_retrival;
    }

}

