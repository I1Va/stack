#ifndef OUTPUT_H
#define OUTPUT_H
#include "general.h"

typedef int stack_elem_t;
#include "stack_funcs.h"

enum log_type_t {
    LOG_ANALYS = 0,
    LOG_DEBUG = 1,
    LOG_ERROR = 2,
};

void print_log_func_info(const char file_name[], const char func_name[], const int line_idx);

ON_HASH(void HASH_print(hash_t *HASH);)

void dump(stack_t *stk, const char file_name[], const char func_name[], const int line_idx);

void log_ptr_stack_dump(enum log_type_t log_type, stack_t *stk, const char file_name[], const char func_name[], const int line_idx);

void print_log_time();

void print_log_type(enum log_type_t log_type);

void print_log_border();

void log_stk_err_print(enum log_type_t log_type, const stk_err err, const char file_name[], const char func_name[], const int line_idx);

void log_init(const char log_path[], stk_err *return_err);

const char *get_log_descr(enum log_type_t log_type);

void log_var_print(enum log_type_t log_type, const char file_name[], const char func_name[], const int line_idx, const char fmt[], ...);

#define LogErr(log_type, err) log_stk_err_print(log_type, err, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);

#define LogVar(log_type, fmt, ...) log_var_print(log_type, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__, fmt, ##__VA_ARGS__);

#define LogStkPtrInfo(log_type, stk) log_ptr_stack_dump(log_type, stk, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);

#endif // OUTPUT_H