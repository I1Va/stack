#ifndef STACK_FUNCS_H
#define STACK_FUNCS_H

#include <cstddef>
#include <stdio.h>

#include "general.h"
#include "string.h"
#include "error_processing.h"

struct stack_t {
    size_t size;
    size_t capacity;
    stack_elem_t *data;

    const char *born_file;
    int born_line;
    const char *born_func;
};

const size_t resize_up_coeff = 2;
const size_t resize_down_check_coeff = 4;
const size_t resize_down_coeff = 2;

const size_t dump_output_sz = 10;

void stack_init(stack_t *stk, const size_t size, const char born_file[] = NULL, const int born_line = 0, const char born_func[] = NULL);

void stack_destroy(stack_t *stk);

void dump(stack_t *stk, const char *file_name, const int line_idx);

err_code verify(stack_t *stk, err_code *return_err, const char *file_name, const char *func_name, const int line_idx);

void resize(stack_t *stk, err_code *return_err);

void stack_push(stack_t *stk, stack_elem_t value, err_code *return_err);

stack_elem_t stack_pop(stack_t *stk, err_code *return_err);

#define DUMP(stk) dump(stk, __FILE__, __LINE__);

#ifdef _DEBUG
    #define VERIFY(stk, return_err, exit_instruction)                                         \
        {                                                                                             \
            if (verify(stk, return_err, __FILE__,__PRETTY_FUNCTION__, __LINE__) != ERR_OK) { \
                exit_instruction;                                                                     \
            }                                                                                          \
        }
    #define STACK_INIT(stk, size) stack_init(stk, size, __FILE__, __LINE__, __PRETTY_FUNCTION__);
#else
    #define VERIFY(stk, return_err, exit_instruction) ;
    #define STACK_INIT(stk, size) stack_init(stk, size);


#endif // _DEBUG

#endif // STACK_FUNCS_H