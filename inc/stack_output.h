#ifndef STK_OUTPUT_H
#define STK_OUTPUT_H

#include "stack_funcs.h"

enum log_type_t {
    LOG_ANALYS = 0,
    LOG_DEBUG = 1,
    LOG_ERROR = 2,
};

void stack_fprintf_border(FILE* stream, const char bord_char, const size_t bord_sz, bool new_line);
void stack_fprintf_title(FILE *stream, const char tittle[], const char bord_char, const size_t bord_sz);

const size_t date_nmemb = 16;
const size_t time_nmemb = 16;

const char *get_log_descr(enum log_type_t log_type);
void print_log_time(FILE *log_output_file_ptr);
void print_log_border(FILE *log_output_file_ptr);
void print_log_func_info(FILE *log_output_file_ptr, const char file_name[], const char func_name[], const int line_idx);
void print_log_type(FILE *log_output_file_ptr, enum log_type_t log_type);
void log_ptr_stack_dump(enum log_type_t log_type, FILE *log_output_file_ptr, stack_t *stk, const char file_name[], const char func_name[], const int line_idx);
void dump(stack_t *stk, FILE* log_output_file_ptr, const char file_name[], const char func_name[], const int line_idx);
void log_stk_err_print(enum log_type_t log_type, FILE *log_output_file_ptr, const stk_err err, const char file_name[], const char func_name[], const int line_idx);
void log_var_print(enum log_type_t log_type, FILE *log_output_file_ptr, const char file_name[], const char func_name[], const int line_idx, const char fmt[], ...);

#define LogErr(log_type, err) log_stk_err_print(log_type, err, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);

#define LogVar(log_type, fmt, ...) log_var_print(log_type, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__, fmt, ##__VA_ARGS__);

#define LogStkPtrInfo(log_type, stk) log_ptr_stack_dump(log_type, stk, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);

#define DUMP(stk, file_ptr) dump(stk, file_ptr, __FILE__, __PRETTY_FUNCTION__, __LINE__);

#endif // OSTK_OUTPUT_H