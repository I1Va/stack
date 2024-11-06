#ifndef STACK_FUNCS_H
#define STACK_FUNCS_H

#include <stdio.h>
#include <string.h>

#include "error_processing.h"
#include "general.h"

struct stack_t {
    size_t size;
    size_t capacity;

    size_t elem_nmemb;

    char *data;

    const char *born_file;
    int born_line;
    const char *born_func;
};

const size_t resize_up_coeff = 2;
const size_t resize_down_check_coeff = 4;
const size_t resize_down_coeff = 2;

const size_t dump_output_sz = 10;

void stack_destroy(stack_t *stk);

stk_err verify(stack_t *stk, stk_err *return_err, const char file_name[], const char func_name[], const int line_idx);

void stack_init(stack_t *stk, const size_t size, const size_t elem_nmemb, stk_err *return_err, const char born_file[] = NULL, const int born_line = 0, const char born_func[] = NULL);

void resize(stack_t *stk, stk_err *return_err);

void stack_push(stack_t *stk, void *value, stk_err *return_err);

bool stack_assign_elem(stack_t *stk, const size_t idx, void *value);

void *stack_get_elem(stack_t *stk, const size_t idx, stk_err *return_err);

void *stack_pop(stack_t *stk, stk_err *return_err);

void *stack_get_last(stack_t *stk, stk_err *return_err);

#endif // STACK_FUNCS_H