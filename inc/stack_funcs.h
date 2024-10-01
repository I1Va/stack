#ifndef STACK_FUNCS_H
#define STACK_FUNCS_H

#include <stdio.h>
#include <string.h>

#include "error_processing.h"
#include "general.h"

typedef unsigned long long canary_elem_t;

const canary_elem_t CANARY_VALUE = 0xC0FFEEABACABABAC;
const size_t CANARY_NMEMB = sizeof(canary_elem_t);

const stack_elem_t POISON_STACK_VALUE = 0x0BAD0DED; // FIXME: использовать при resize

struct canaries_t {
    const canary_elem_t *canary_left_ptr;
    const canary_elem_t *canary_mid_ptr;
    const canary_elem_t *canary_stk_right_ptr;
    const canary_elem_t *canary_stk_left_ptr;
};

struct hash_t {
    void *struct_left;
    void *struct_right;
    void *data_left;
    void *data_right;

    unsigned long long hash_value;
    // unsigned long long hash_mod
    unsigned long long hash_mult = 31;
};

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

canary_elem_t *stack_end_canary_getptr(stack_t *stk);

ON_HASH ( // TODO: сделать такое же для функций CANARY
    void HASH_print();

    unsigned long long HASH_get();

    void HASH_rebuild(stack_t *stk, stack_elem_t *data_ptr, const size_t n_bytes);

    bool HASH_check();
)


void stack_end_canary_assign(stack_t *stk, const canary_elem_t value);

void stack_init(stack_t *stk, const size_t size, err_code *return_err, const char born_file[] = NULL, const int born_line = 0, const char born_func[] = NULL);

void stack_destroy(stack_t *stk);

void dump(stack_t *stk, const char *file_name, const int line_idx);

err_code verify(stack_t *stk, err_code *return_err, const char *file_name, const char *func_name, const int line_idx);

void stack_memset(stack_elem_t *data, const stack_elem_t value, const size_t n);

void resize(stack_t *stk, err_code *return_err);

void stack_push(stack_t *stk, stack_elem_t value, err_code *return_err);

stack_elem_t stack_pop(stack_t *stk, err_code *return_err);

#endif // STACK_FUNCS_H