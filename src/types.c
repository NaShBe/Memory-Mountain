#include "types.h"
#include "string.h"

mm_string_t* create_string(char* const string)
{
    mm_string_t* ret_str = malloc (sizeof(mm_string_t));
    if (ret_str != NULL)
    {
        ret_str->len = strlen(string);
        ret_str->str = malloc (ret_str->len + 1);
        if (ret_str->str == NULL)
        {
            free(ret_str);
            return NULL;
        }
        memcpy(ret_str->str, string, ret_str->len);
        return ret_str;
    }
    return NULL;
}

void write_to_string(mm_string_t* dest, char* const src)
{
    if (dest != NULL && src != NULL)
    {
        size_t temp_len = strlen(src);
        mm_char_t* str = malloc(sizeof(temp_len) + 1);
        if (str != NULL)
        {
            if (dest->str != NULL)
            {
                free(dest->str);
            }
            dest->str = str;
            dest->len = temp_len;
        }
    }
}

void free_string(mm_string_t** str)
{
    if (str != NULL && *str != NULL)
    {
        if ((*str)->str != NULL)
        {
            free((*str)->str);
        }
        free(*str);
        *str = NULL;
    }
}
