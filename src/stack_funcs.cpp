
#include "general.h"
#include "error_processing.h"
#include <cstdlib>

typedef int stack_elem_t;
#include "stack_funcs.h"

stack_t *stack_init(const size_t size) {
    stack_t *stk = (stack_t *) calloc(1, sizeof(stack_t));
    if (stk == NULL) {
        DEBUG_ERROR(ERR_CALLOC)
        CLEAR_MEMORY(exit_mark)
    }

    stk->size = 0;
    stk->capacity = size;

    stk->data = (stack_elem_t *) calloc(stk->capacity, sizeof(stack_elem_t));
    if (stk->data == NULL) {
        DEBUG_ERROR(ERR_CALLOC)
        CLEAR_MEMORY(exit_mark)
    }

    return stk;

    exit_mark:
    if (stk != NULL) {
        FREE(stk);
    }
    if (stk->data != NULL) {
        FREE(stk->data);
    }

    return NULL;
}

void stack_destroy(stack_t *stk) {
    FREE(stk->data);
    FREE(stk);
}

// void stack_push(stack_t *stk, stack_elem_t value, err_code *return_err) {

// }