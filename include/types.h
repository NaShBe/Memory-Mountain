#ifndef NASHBE_TYPES_H
#define NASHBE_TYPES_H

#include "port.h"
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

#ifdef __cplusplus__
extern "C"{
#endif

// C data primitives
typedef const char*             mm_strltr_t;    // string literal representation
typedef char*                   mm_charptr_t;   // character pointer representation
typedef char                    mm_char_t;      // character representation
typedef int                     mm_int_t;       // integer representation
typedef unsigned int            mm_uint_t;      // unsigned integer representation
typedef float                   mm_spfloat_t;   // single-point floating point representation
typedef double                  mm_dpfloat_t;   // double-precision floating point representation
typedef long double             mm_epfloat_t;   // extended-percision floating point representation
typedef float                   mm_float_t;     // generalized floating point representation

// Library data primitives
typedef bool                    mm_bool_t;
#if CHAR_BIT % 8 == 0 && CHAR_BIT % 16 != 0
typedef int8_t                  mm_int8_t;
typedef uint8_t                 mm_uint8_t;
#endif
#if CHAR_BIT % 8 == 0 || CHAR_BIT % 16 == 0
typedef int16_t                 mm_int16_t;
typedef uint16_t                mm_uint16_t;
typedef int32_t                 mm_int32_t;
typedef uint32_t                mm_uint32_t;
#endif
#if PORT_SYS_COMP == SYS_COMP_GCC || PORT_SYS_COMP == SYS_COMP_CLANG
    #ifdef _____LP64_____
        typedef int64_t         mm_int64_t;
        typedef uint64_t        mm_uint64_t;
    #endif
#elif PORT_SYS_OS == SYS_OS_WIN64
    typedef int64_t             mm_int64_t;
    typedef uint64_t            mm_uint64_t;
#endif
typedef intmax_t                mm_intmax_t;
typedef uintmax_t               mm_uintmax_t;

// project-defined types
typedef struct mm_string_t      mm_string_t;    // string representation
struct mm_string_t
{
    mm_charptr_t    str;                        // pointer to DYNAMICALLY allocated string
    size_t          len;                        // lenght of that string
};

extern void write_to_string(char* const, mm_string_t);
extern void free_string(mm_string_t);

#ifdef __cplusplus__
}
#endif
#endif