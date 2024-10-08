#ifndef ERROR_PROCESSING_H
#define ERROR_PROCESSING_H

enum err_code {
    ERR_OK                         = 0,
    ERR_NULLPTR                    = 1 << 1,
    ERR_CALLOC                     = 1 << 2,
    ERR_MEM                        = 1 << 3,
    ERR_UNKNOWN                    = 1 << 4,
    ERR_STAT                       = 1 << 5,
    ERR_INPUT_DATA                 = 1 << 6,
    ERR_FILE_OPEN                  = 1 << 7,
    ERR_FILE_CLOSE                 = 1 << 8,
    ERR_ARGS                       = 1 << 9,
    ERR_WRONG_COEF                 = 1 << 10,
    ERR_INIT                       = 1 << 11,
    ERR_STACK_NULLPTR              = 1 << 12,
    ERR_STACK_CONT_NULLPTR         = 1 << 13,
    ERR_STACK_OVERFLOW             = 1 << 14,
    ERR_STACK_POP                  = 1 << 15,
    ERR_REALLOC                    = 1 << 16,
    ERR_CANARY_LEFT                = 1 << 17,
    ERR_CANARY_MID                 = 1 << 18,
    ERR_CANARY_RIGHT               = 1 << 19,
    ERR_CANARY_STK_RIGHT           = 1 << 20,
    ERR_HASH_STACK_DATA_MISMATCH   = 1 << 21,
    ERR_CANARY_STK_LEFT            = 1 << 22,
    ERR_SYSTEM                     = 1 << 23,
    ERR_STACK_LAST_ELEM            = 1 << 24,
    ERR_HASH_STACK_STRUCT_MISMATCH = 1 << 25,
};

const char *get_descr(unsigned long long err);

int fprintf_abort(const char file_name[], const int line, const char function_name[], const char error_descr[]);

// err_code fprintf_return(const char file_name[], const int line, const char function_name[], const err_code code);

// #ifndef _REALIZE
//     #define asserted(code) ? 1 : printf_red(stderr, "{%s}; [%s: %d]; err_info: %s\n", __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__, get_descr(code));
// #else
//     #define asserted(code) ;
// #endif // _REALIZE

#endif // ERROR_PROCESSING_H
