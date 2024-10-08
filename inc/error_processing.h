#ifndef ERROR_PROCESSING_H
#define ERROR_PROCESSING_H

enum err_code {
    ERR_OK                         = 0,
    ERR_NULLPTR                    = 1,
    ERR_CALLOC                     = 2,
    ERR_MEM                        = 3,
    ERR_UNKNOWN                    = 4,
    ERR_STAT                       = 5,
    ERR_INPUT_DATA                 = 6,
    ERR_FILE_OPEN                  = 7,
    ERR_FILE_CLOSE                 = 8,
    ERR_ARGS                       = 9,
    ERR_WRONG_COEF                 = 10,
    ERR_INIT                       = 11,
    ERR_STACK_NULLPTR              = 12,
    ERR_STACK_CONT_NULLPTR         = 13,
    ERR_STACK_OVERFLOW             = 14,
    ERR_STACK_POP                  = 15,
    ERR_REALLOC                    = 16,
    ERR_CANARY_LEFT                = 17,
    ERR_CANARY_MID                 = 18,
    ERR_CANARY_RIGHT               = 19,
    ERR_CANARY_STK_RIGHT           = 20,
    ERR_HASH_STACK_DATA_MISMATCH   = 21,
    ERR_CANARY_STK_LEFT            = 22,
    ERR_SYSTEM                     = 23,
    ERR_STACK_LAST_ELEM            = 24,
    ERR_HASH_STACK_STRUCT_MISMATCH = 25,
};

enum err_code_bit {
    ERR_OK_BIT                         = 1 << 0,
    ERR_NULLPTR_BIT                    = 1 << 1,
    ERR_CALLOC_BIT                     = 1 << 2,
    ERR_MEM_BIT                        = 1 << 3,
    ERR_UNKNOWN_BIT                    = 1 << 4,
    ERR_STAT_BIT                       = 1 << 5,
    ERR_INPUT_DATA_BIT                 = 1 << 6,
    ERR_FILE_OPEN_BIT                  = 1 << 7,
    ERR_FILE_CLOSE_BIT                 = 1 << 8,
    ERR_ARGS_BIT                       = 1 << 9,
    ERR_WRONG_COEF_BIT                 = 1 << 10,
    ERR_INIT_BIT                       = 1 << 11,
    ERR_STACK_NULLPTR_BIT              = 1 << 12,
    ERR_STACK_CONT_NULLPTR_BIT         = 1 << 13,
    ERR_STACK_OVERFLOW_BIT             = 1 << 14,
    ERR_STACK_POP_BIT                  = 1 << 15,
    ERR_REALLOC_BIT                    = 1 << 16,
    ERR_CANARY_LEFT_BIT                = 1 << 17,
    ERR_CANARY_MID_BIT                 = 1 << 18,
    ERR_CANARY_RIGHT_BIT               = 1 << 19,
    ERR_CANARY_STK_RIGHT_BIT           = 1 << 20,
    ERR_HASH_STACK_DATA_MISMATCH_BIT   = 1 << 21,
    ERR_CANARY_STK_LEFT_BIT            = 1 << 22,
    ERR_SYSTEM_BIT                     = 1 << 23,
    ERR_STACK_LAST_ELEM_BIT            = 1 << 24,
    ERR_HASH_STACK_STRUCT_MISMATCH_BIT = 1 << 25,
};

const char *get_descr(enum err_code err = ERR_UNKNOWN);

int fprintf_abort(const char file_name[], const int line, const char function_name[], const char error_descr[]);

err_code fprintf_return(const char file_name[], const int line, const char function_name[], const err_code code);

// #ifndef _REALIZE
//     #define asserted(code) ? 1 : printf_red(stderr, "{%s}; [%s: %d]; err_info: %s\n", __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__, get_descr(code));
// #else
//     #define asserted(code) ;
// #endif // _REALIZE


// #define error_pull_up(condition, code) if (!condition) {fprintf_red(stderr, "{%s}; [%s: %d]; err_info: %s\n", __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__, get_descr(code)); return code;}

#endif // ERROR_PROCESSING_H
