#include <string.h>

#include "error_processing.h"

// #define DESCR_(code) case code : return #code;

#define DESCR_(code, err)   \
{                                   \
    if (code & err) {           \
        return #err;            \
    }                               \
}                                   \

const char *get_descr(unsigned long long err) {
    DESCR_(err, ERR_NULLPTR)
    DESCR_(err, ERR_CALLOC)
    DESCR_(err, ERR_UNKNOWN)
    DESCR_(err, ERR_STAT)
    DESCR_(err, ERR_INPUT_DATA)
    DESCR_(err, ERR_FILE_OPEN)
    DESCR_(err, ERR_FILE_CLOSE)
    DESCR_(err, ERR_ARGS)
    DESCR_(err, ERR_WRONG_COEF)
    DESCR_(err, ERR_INIT)
    DESCR_(err, ERR_STACK_NULLPTR)
    DESCR_(err, ERR_STACK_CONT_NULLPTR)
    DESCR_(err, ERR_STACK_OVERFLOW)
    DESCR_(err, ERR_STACK_POP)
    DESCR_(err, ERR_REALLOC)

    DESCR_(err, ERR_CANARY_MID)
    DESCR_(err, ERR_CANARY_RIGHT)
    DESCR_(err, ERR_CANARY_STK_RIGHT)
    DESCR_(err, ERR_CANARY_STK_LEFT)

    DESCR_(err, ERR_HASH_STACK_DATA_MISMATCH)
    DESCR_(err, ERR_HASH_STACK_STRUCT_MISMATCH)
    DESCR_(err, ERR_STACK_LAST_ELEM)

    DESCR_(err, ERR_SYSTEM)

    if (err == ERR_OK) {
        return "ERR_OK";
    }

    return "STRANGE ERROR!";
}


// #undef DESCR_
#undef DESCR_