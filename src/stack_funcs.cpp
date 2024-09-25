
#include "general.h"
#include "error_processing.h"
#include <cassert>
#include <cstdlib>

typedef int stack_elem_t;
#include "stack_funcs.h"

void dump(FILE *stream, stack_t *stk, const char *file_name, const int line_idx) {
    if (stk == NULL) {
        return;
    }
    fprintf_red(stream, "stack_t [%p] at %s:%d born at %s:%d(%s)\n{\n", \
    stk, file_name, line_idx, stk->born_file, stk->born_line, stk->born_func);

    fprintf_red(stream, "size = %lu\n", stk->size);
    fprintf_red(stream, "capacity = %lu\n", stk->capacity);
    fprintf_red(stream, "data[%p]\n", stk->data);

    fprintf_red(stream, "{\n");
    if (stk->data == NULL) {
        fprintf_red(stream, "NULLPTR\n");
    } else {
        for (size_t i = 0; i < stk->capacity; i++) {
            fprintf_red(stream, "[%lu] = %d;\n", i, stk->data[i]);
        }
    }
    fprintf_red(stream, "}\n");

    fprintf_red(stream, "}\n");
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

    fprintf_red(stream, "{%s} [%s: %d]: descr{%s}\n", file_name, func_name, line_idx, get_descr(*return_err));
    dump(stream, stk, file_name, line_idx);

    return *return_err;
}

stack_t *stack_init(const size_t size, const char born_file[], const int born_line, const char born_func[]) {
    stack_t *stk = (stack_t *) calloc(1, sizeof(stack_t));
    if (stk == NULL) {
        DEBUG_ERROR(ERR_CALLOC)
        CLEAR_MEMORY(exit_mark)
    }

    stk->size = 0;
    stk->capacity = size;

    stk->born_file = born_file;
    stk->born_line = born_line;
    stk->born_func = born_func;

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

    VERIFY(stderr, stk, return_err, return) // TODO: нетревиальный макрос. написать документацию к нему
    if (stk->size + 1 == stk->capacity) {
        // TODO: realloc
    }
    stk->data[stk->size++] = value;
    VERIFY(stderr, stk, return_err, return)

}