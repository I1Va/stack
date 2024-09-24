#ifndef STACK_FUNCS_H
#define STACK_FUNCS_H

#include <cstddef>
#include "string.h"

struct stack_t {
    size_t size;
    size_t capacity;
    stack_elem_t *data;
};

// const size_t stack_capacity_start_val = 128;

stack_t *stack_init(const size_t size);

void stack_destroy(stack_t *stk);

#endif // STACK_FUNCS_H