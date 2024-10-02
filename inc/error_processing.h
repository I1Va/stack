#ifndef ERROR_PROCESSING_H
#define ERROR_PROCESSING_H

enum err_code {
    ERR_OK = 0,
    ERR_NULLPTR = 1, // TODO: подравняй нумерацию
    ERR_CALLOC = 2,
    ERR_MEM = 3,
    ERR_UNKNOWN = 4,
    ERR_STAT = 5,
    ERR_INPUT_DATA = 6,
    ERR_FILE_OPEN = 7,
    ERR_FILE_CLOSE = 8,
    ERR_ARGS = 9,
    ERR_WRONG_COEF = 10,
    ERR_INIT = 11,

    ERR_STACK_NULLPTR = 12,
    ERR_STACK_CONT_NULLPTR = 13,
    ERR_STACK_OVERFLOW = 14,
    ERR_STACK_POP = 15,
    ERR_REALLOC = 16,

    ERR_CANARY_LEFT = 17,
    ERR_CANARY_MID = 18,
    ERR_CANARY_RIGHT = 19,
    ERR_CANARY_STK_RIGHT = 20,
    ERR_HASH_MISMATCH = 21,
    ERR_CANARY_STK_LEFT = 22,
    // TODO: сделать ошибки через битмаски
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
