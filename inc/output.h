#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>

#include "general.h"

typedef long long stack_elem_t;
#include "stack_funcs.h"

void ptr_stack_dump(stack_t *stk);

ON_HASH(void HASH_print(hash_t *HASH);)

void dump(stack_t *stk, const char *file_name, const int line_idx);

void print_err_full_description(const unsigned long long err);

void log_init(const char log_path[], unsigned long long *return_err);

void log_var_print(const char* fmt, ...);

#define LogVar(str_, ...) log_var_print("{%s} [%s: %d]: descr{" str_ "}\n", __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);

#endif // OUTPUT_H