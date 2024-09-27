#ifndef STACK_FUNCS_H
#define STACK_FUNCS_H

#include <string.h>
#include "error_processing.h"
#include "general.h"

const unsigned long long CANARY_VALUE = 0xC0FFEEABACABABAC;

struct stack_t {
    ON_CANARY(const unsigned long long CANARY_LEFT = CANARY_VALUE;)

    size_t size;
    size_t capacity;

    ON_CANARY(const unsigned long long CANARY_MID = CANARY_VALUE;)

    stack_elem_t *data;

    const char *born_file;
    int born_line;
    const char *born_func;
};

const size_t resize_up_coeff = 2;
const size_t resize_down_check_coeff = 4;
const size_t resize_down_coeff = 2;

const size_t dump_output_sz = 10;

void stack_init(stack_t *stk, const size_t size, err_code *return_err, const char born_file[] = NULL, const int born_line = 0, const char born_func[] = NULL);

void stack_destroy(stack_t *stk);

void dump(stack_t *stk, const char *file_name, const int line_idx);

err_code verify(stack_t *stk, err_code *return_err, const char *file_name, const char *func_name, const int line_idx);

void resize(stack_t *stk, err_code *return_err);

void stack_push(stack_t *stk, stack_elem_t value, err_code *return_err);

stack_elem_t stack_pop(stack_t *stk, err_code *return_err);

#endif // STACK_FUNCS_H