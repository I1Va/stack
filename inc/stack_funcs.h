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

const size_t dump_output_sz = 10;

stack_t *stack_init(const size_t size, const char born_file[], const int born_line, const char born_func[]);

void stack_destroy(stack_t *stk);

void dump(FILE *stream, stack_t *stk, const char *file_name, const int line_idx);

err_code verify(FILE *stream, stack_t *stk, err_code *return_err, const char *file_name, const char *func_name, const int line_idx);

void stack_push(stack_t *stk, stack_elem_t value, err_code *return_err);

stack_elem_t stack_pop(stack_t *stk, err_code *return_err);

#define DUMP(stream, stk) dump(stream, stk, __FILE__, __LINE__);

#ifdef _DEBUG
    #define VERIFY(stream, stk, return_err, exit_instruction)                                         \
        {                                                                                             \
            if (verify(stream, stk, return_err, __FILE__,__PRETTY_FUNCTION__, __LINE__) != ERR_OK) { \
                exit_instruction;                                                                     \
            }                                                                                          \
        }
    #define INIT(size) stack_init(size, __FILE__, __LINE__, __PRETTY_FUNCTION__);
#else
    #define VERIFY(stream, stk, return_err, exit_instruction) ;
    #define INIT(size) stack_init(size, "0", 0, "0");


#endif // _DEBUG

#endif // STACK_FUNCS_H