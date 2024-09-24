#ifndef STACK_FUNCS_H
#define STACK_FUNCS_H

#include <cstddef>
#include <stdio.h>

#include "string.h"
#include "error_processing.h"

struct stack_t {
    size_t size;
    size_t capacity;
    stack_elem_t *data;
};

// const size_t stack_capacity_start_val = 128;

stack_t *stack_init(const size_t size);

void stack_destroy(stack_t *stk);

void dump(FILE *stream, stack_t *stk, const char *file_name, const char *func_name, const int line_idx);

err_code verify(FILE *stream, stack_t *stk, err_code *return_err, const char *file_name, const char *func_name, const int line_idx);

void stack_push(stack_t *stk, stack_elem_t value, err_code *return_err);

#define VERIFY(stream, stk, return_err, exit_instruction)                     \
    {                                                          \
        if (verify(stream, stk, return_err, __FILE__, __PRETTY_FUNCTION__, __LINE__) != ERR_OK) { \
            exit_instruction;                                                 \
        }                                                                                   \
    }

#endif // STACK_FUNCS_H