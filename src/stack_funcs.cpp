
#include "general.h"
#include "error_processing.h"
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstring>

typedef int stack_elem_t;
#include "stack_funcs.h"

FILE *dump_output_file_ptr = stderr;
const stack_elem_t POISON_STACK_VALUE = 0x0BAD0DED;

void dump(stack_t *stk, const char *file_name, const int line_idx) {
    if (stk == NULL) {
        return;
    }
    fprintf_red(dump_output_file_ptr, "stack_t [%p] at %s:%d born at %s:%d(%s)\n", \
    stk, file_name, line_idx, stk->born_file, stk->born_line, stk->born_func);

    fprintf_wht(dump_output_file_ptr, "{\n");

    fprintf_yel(dump_output_file_ptr, "size = %lu\n", stk->size);
    fprintf_yel(dump_output_file_ptr, "capacity = %lu\n", stk->capacity);
    fprintf_yel(dump_output_file_ptr, "data[%p]\n", stk->data);

    fprintf_wht(dump_output_file_ptr, "{\n");
    if (stk->data == NULL) {
        fprintf_red(dump_output_file_ptr, "NULLPTR\n");
    } else {
        for (size_t i = 0; i < stk->capacity; i++) {
            fprintf_grn(dump_output_file_ptr, "[%lu] = %d;\n", i, stk->data[i]);
        }
    }
    fprintf_wht(dump_output_file_ptr, "}\n");

    fprintf_wht(dump_output_file_ptr, "}\n");
}

err_code verify(stack_t *stk, err_code *return_err, const char *file_name, const char *func_name, const int line_idx) {
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

    fprintf_red(dump_output_file_ptr, "{%s} [%s: %d]: descr{%s}\n", file_name, func_name, line_idx, get_descr(*return_err));
    dump(stk, file_name, line_idx);

    return *return_err;
}

void stack_init(stack_t *stk, const size_t size, err_code *return_err, const char born_file[], const int born_line, const char born_func[]) {

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
        *return_err = ERR_CALLOC;
        DEBUG_ERROR(ERR_CALLOC)
        CLEAR_MEMORY(exit_mark)
    }
    // memset(stk->data, POISON_STACK_VALUE, stk->capacity);

    return;

    exit_mark:
    if (stk != NULL) {
        FREE(stk);
    }
    if (stk->data != NULL) {
        FREE(stk->data);
    }

    return;
}

void stack_destroy(stack_t *stk) {
    FREE(stk->data);
}

void resize(stack_t *stk, err_code *return_err) {
    assert(stk != NULL);
    assert(return_err != NULL);

    if (stk->size + 1 == stk->capacity) {
        stk->capacity *= resize_up_coeff;
    } else if (stk->size + 1 <= stk->capacity / resize_down_check_coeff) {
        stk->capacity /= resize_down_coeff;
    } else {
        return;
    }

    stack_elem_t *tmp_stk_ptr = (stack_elem_t *) realloc(stk->data, stk->capacity * sizeof(stack_elem_t));
    // memset(stk->data + stk->size, POISON_STACK_VALUE, stk->capacity - stk->size); //TODO: как заполнить стэк значениями POISON?

    if (tmp_stk_ptr == NULL) {
        *return_err = ERR_REALLOC;
        DEBUG_ERROR(*return_err);
        return;
    }

    stk->data =  tmp_stk_ptr;
}

void stack_push(stack_t *stk, stack_elem_t value, err_code *return_err) {
    assert(return_err != NULL);

    VERIFY(stk, return_err, return) // TODO: нетревиальный макрос. написать документацию к нему
    // VERIFY(stderr, stk, return_err, return) вместо stderr сделать глобальную переменную FILE *
    // переименовать в ASSERT так как убирается в релизе
    // verify проверяется в релизе
    err_code last_err = ERR_OK;

    resize(stk, &last_err);
    if (last_err != ERR_OK) {
        *return_err = last_err;
        DEBUG_ERROR(last_err);
        return;
    }

    stk->data[stk->size++] = value;
    VERIFY(stk, return_err, return)
}

stack_elem_t stack_pop(stack_t *stk, err_code *return_err) {
    assert(return_err != NULL);

    VERIFY(stk, return_err, return 0) // TODO: нетревиальный макрос. написать документацию к нему

    err_code last_err = ERR_OK;

    if (stk->size == 0) {
        *return_err = ERR_STACK_POP;
        DEBUG_ERROR(*return_err);
        return 0;
    }

    resize(stk, &last_err);
    if (last_err != ERR_OK) {
        *return_err = last_err;
        DEBUG_ERROR(last_err);
        return 0;
    }

    stack_elem_t last_elem = stk->data[--stk->size];
    stk->data[stk->size] = 0;
    return last_elem;

}
