#include <stdlib.h>

#include "error_processing.h"

#define DESCR_(code) case code : return #code;

const char *get_descr(enum err_code err) {
    switch (err) {
        DESCR_(ERR_OK)
        DESCR_(ERR_UNKNOWN)
        DESCR_(ERR_CALLOC)
        DESCR_(ERR_NULLPTR)
        DESCR_(ERR_STAT)
        DESCR_(ERR_INPUT_DATA)
        DESCR_(ERR_MEM)
        DESCR_(ERR_FILE_CLOSE)
        DESCR_(ERR_FILE_OPEN)
        DESCR_(ERR_ARGS)
        DESCR_(ERR_WRONG_COEF)
        DESCR_(ERR_INIT)
        DESCR_(ERR_STACK_NULLPTR)
        DESCR_(ERR_STACK_CONT_NULLPTR)
        DESCR_(ERR_STACK_OVERFLOW)
        DESCR_(ERR_STACK_POP)
        DESCR_(ERR_REALLOC)
        DESCR_(ERR_CANARY_LEFT)
        DESCR_(ERR_CANARY_MID)
        default: return "VERY STRANGE ERROR:(";
    }
}

#undef DESCR_