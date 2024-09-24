
#include "general.h"
#include "error_processing.h"
#include <cassert>
#include <cstdlib>

typedef int stack_elem_t;
#include "stack_funcs.h"

void dump(FILE *stream, stack_t *stk, const char *file_name, const char *func_name, const int line_idx) {
    fprintf_red(stream, "there should be stack dump output here: {%p} {%s} {%s} {%d}\n", stk, file_name, func_name, line_idx);
}

err_code verify(FILE *stream, stack_t *stk, err_code *return_err, const char *file_name, const char *func_name, const int line_idx) {
    if (stk == NULL) {
        *return_err = ERR_STACK_NULLPTR;
        goto dump_mark;
    }

    if (stk->data == NULL) {
        *return_err = ERR_STACK_CONT_NULLPTR;
        goto dump_mark;
    }

    if (stk->size >= stk->capacity) {
        *return_err = ERR_STACK_OVERFLOW;
        goto dump_mark;
    }

    return ERR_OK;

    dump_mark:

    DEBUG_ERROR(*return_err);
    dump(stream, stk, file_name, func_name, line_idx);

    return *return_err;
}




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

void stack_push(stack_t *stk, stack_elem_t value, err_code *return_err) {
    assert(return_err != NULL);
    if (value) {}
    VERIFY(stderr, stk, return_err, return)



}