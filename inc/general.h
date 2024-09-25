#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
#include <time.h>

#define GRN "\e[0;32m"
#define WHT "\e[0;20m"
#define RED "\e[0;31m"
#define YEL "\e[0;33m"

#define printf_red(str_, ...) printf(RED str_ WHT, ##__VA_ARGS__) // TODO: дефайны КАПСОМ
#define printf_wht(str_, ...) printf(WHT str_ WHT, ##__VA_ARGS__)
#define printf_grn(str_, ...) printf(GRN str_ WHT, ##__VA_ARGS__)
#define printf_yel(str_, ...) printf(YEL str_ WHT, ##__VA_ARGS__)

#define fprintf_red(stream, str_, ...) fprintf(stream, RED str_ WHT, ##__VA_ARGS__)
#define fprintf_wht(stream, str_, ...) fprintf(stream, WHT str_ WHT, ##__VA_ARGS__)
#define fprintf_grn(stream, str_, ...) fprintf(stream, GRN str_ WHT, ##__VA_ARGS__)
#define fprintf_yel(stream, str_, ...) fprintf(stream, YEL str_ WHT, ##__VA_ARGS__)

#define FREE(ptr)              \
    do {                       \
        free(ptr); ptr = NULL; \
    } while(0);


/*
#define FREE(ptr)                \
    ({                           \
        typeof(ptr) ptr__ = ptr; \
        free(ptr);               \
        ptr = NULL;              \
        ptr__                    \
    })
*/

enum RETURN_STATES {
    ReturnErrOR  = -1,
    RETURN_FALSE =  0,
    RETURN_TRUE  =  1,
};

#define CLEAR_MEMORY(mark) goto mark;

#ifdef _DEBUG
    #define debug(str_, ...) fprintf_red(stderr, "{%s} [%s: %d]: descr{" str_ "}\n", __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
    #define DEBUG_ERROR(code) fprintf_red(stderr, "{%s} [%s: %d]: descr{%s}\n", __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__, get_descr(code));
    #define ON_DEBUG(...) __VA_ARGS__
#else
    #define debug(str_, ...) ;
    #define DEBUG_ERROR(code) ;
    #define ON_DEBUG(...) ;
#endif // _DEBUG

#endif // ARRAY_H
