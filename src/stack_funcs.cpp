
#include "general.h"
#include "error_processing.h"
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>

typedef int stack_elem_t;
#include "stack_funcs.h"

FILE *dump_output_file_ptr = stderr;

ON_CANARY(canaries_t CANARIES = {};)

ON_HASH(hash_t HASH = {};)

void stack_memset(stack_elem_t *data, const stack_elem_t value, const size_t n) {
    for (size_t i = 0; i < n; i++) {
        *(data + i) = value;
    }
}

void dump(stack_t *stk, const char *file_name, const int line_idx) {
    if (stk == NULL) {
        return;
    }
    fprintf_red(dump_output_file_ptr, "stack_t [%p] at %s:%d born at %s:%d(%s)\n", \
    stk, file_name, line_idx, stk->born_file, stk->born_line, stk->born_func);

    fprintf_wht(dump_output_file_ptr, "{\n");
    ON_CANARY(fprintf_yel(dump_output_file_ptr, "canl_ptr[%p]\n", &stk->CANARY_LEFT);)
    fprintf_yel(dump_output_file_ptr, "size = %lu\n", stk->size);
    // fprintf_yel(dump_output_file_ptr, "size_ptr[%p]\n", &stk->size);
    fprintf_yel(dump_output_file_ptr, "capacity = %lu\n", stk->capacity);
    // fprintf_yel(dump_output_file_ptr, "capa_ptr[%p]\n", &stk->capacity);
    // fprintf_yel(dump_output_file_ptr, "data_ptr[%p]\n", &stk->data);
    fprintf_yel(dump_output_file_ptr, "stack[%p]\n", stk->data);

    fprintf_wht(dump_output_file_ptr, "{\n");
    if (stk->data == NULL) {
        fprintf_red(dump_output_file_ptr, "NULLPTR\n");
    } else {
        for (size_t i = 0; i < stk->capacity; i++) {
            if (stk->data[i] == POISON_STACK_VALUE) {
                fprintf_grn(dump_output_file_ptr, "[%lu] = POISON;\n", i);
            } else {
                fprintf_grn(dump_output_file_ptr, "*[%lu] = %d;\n", i, stk->data[i]);
            }
        }
        ON_CANARY(
            canary_elem_t canary_val = *stack_end_canary_getptr(stk);
            fprintf_grn(dump_output_file_ptr, "[-1] = %llx;\n", canary_val); //FIXME: %x? для unsigned long long работает?
        )
    }
    fprintf_wht(dump_output_file_ptr, "}\n");

    fprintf_wht(dump_output_file_ptr, "}\n");
}

err_code verify(stack_t *stk, err_code *return_err, const char *file_name, const char *func_name, const int line_idx) {

    ON_CANARY( // FIXME: копипаст. Можно просто сделать массив с указателями на канарейки и выдавать индекс ломанной (с описанием)
        if (*CANARIES.canary_left_ptr != CANARY_VALUE) {
            MY_ASSERT(ERR_CANARY_LEFT, abort())
        }
    )

    ON_CANARY(
        if (*CANARIES.canary_mid_ptr != CANARY_VALUE) {
            MY_ASSERT(ERR_CANARY_MID, abort())
            assert(0);
        }
    )

    ON_CANARY(
        if (*CANARIES.canary_stk_right_ptr != CANARY_VALUE) {
            MY_ASSERT(ERR_CANARY_STK_RIGHT, abort())
            assert(0);
        }
    )

    ON_HASH(
        if (HASH.hash_value != HASH_get()) {
            HASH_print();
            printf("hash_value: [%llu]\n", HASH.hash_value);
            MY_ASSERT(ERR_HASH_MISMATCH, abort())
            assert(0);
        }
    )


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

    ON_CANARY(CANARIES.canary_left_ptr = &stk->CANARY_LEFT;)

    stk->size = 0;
    stk->capacity = size;

    ON_CANARY(CANARIES.canary_mid_ptr = &stk->CANARY_MID;)

    NOT_ON_CANARY(stk->data = (stack_elem_t *) calloc(stk->capacity, sizeof(stack_elem_t));)
    ON_CANARY(stk->data = (stack_elem_t *) calloc(stk->capacity * sizeof(stack_elem_t) + 2 * CANARY_NMEMB, sizeof(char));)

    if (stk->data == NULL) {
        *return_err = ERR_CALLOC;
        DEBUG_ERROR(ERR_CALLOC)
        CLEAR_MEMORY(exit_mark)
    }

    stack_memset(stk->data, POISON_STACK_VALUE, stk->capacity);

    ON_CANARY(
        stack_end_canary_assign(stk, CANARY_VALUE);
        CANARIES.canary_stk_right_ptr = stack_end_canary_getptr(stk);
    )

    stk->born_file = born_file;
    stk->born_line = born_line;
    stk->born_func = born_func;

    ON_HASH(
        HASH_rebuild_ptr(stk, stk->data, stk->capacity * sizeof(stack_elem_t) + 2 * CANARY_NMEMB);
        HASH_rebuild_value();
    )


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

ON_HASH(
    void HASH_print() {
        printf("struct_seg: [%p - %p)\n", HASH.struct_left, HASH.struct_right);
        printf("stackd_seg: [%p - %p)\n", HASH.data_left, HASH.data_right);
        printf("hash_value: [%llu]\n", HASH.hash_value);
    }

    unsigned long long HASH_get() {
        char *left_ptr = (char *) HASH.struct_left;
        char *right_ptr = (char *) HASH.struct_right;
        unsigned long long hash_value = 0;

        while (left_ptr < right_ptr) {
            hash_value += *left_ptr++ * HASH.hash_mult; // использую переполнение
        }

        left_ptr = (char *) HASH.data_left;
        right_ptr = (char *) HASH.data_right;

        while (left_ptr < right_ptr) {
            hash_value += *left_ptr++ * HASH.hash_mult; // использую переполнение
        }

        return hash_value;
    }

    void HASH_rebuild_ptr(stack_t *stk, stack_elem_t *data_ptr, const size_t n_bytes) {
        HASH.struct_left = stk;
        HASH.struct_right = stk + 1;
        HASH.data_left = data_ptr;
        HASH.data_right = (char *) data_ptr + n_bytes;
    }

    void HASH_rebuild_value() {
        HASH.hash_value = HASH_get();
    }

    bool HASH_check() {
        return HASH.hash_value == HASH_get();
    }
)

ON_CANARY(
    canary_elem_t *stack_end_canary_getptr(stack_t *stk) {
        size_t stack_byte_size = stk->capacity * sizeof(stack_elem_t);
        canary_elem_t *canary_ptr = (canary_elem_t *)((char *) stk->data + stack_byte_size);
        canary_ptr = (canary_elem_t *) ((char *) (canary_ptr) + (unsigned long long) canary_ptr % 8ull); // FIXME: корявый нечитаемый padding fix. Придумать что-то по изящней
        return canary_ptr;
    }

    void stack_end_canary_assign(stack_t *stk, const canary_elem_t value) {
        canary_elem_t *canary_ptr = stack_end_canary_getptr(stk);
        *canary_ptr = value;
    }
)

void stack_destroy(stack_t *stk) {
    FREE(stk->data);
}

void resize(stack_t *stk, err_code *return_err) {
    assert(stk != NULL);
    assert(return_err != NULL);

    bool resize_up_state = false;
    size_t new_byte_size = 0;

    if (stk->size + 1 == stk->capacity) {
        ON_CANARY(stack_end_canary_assign(stk, 0));
        stk->capacity *= resize_up_coeff;
        resize_up_state = true;
    } else if (stk->size + 1 <= stk->capacity / resize_down_check_coeff) {
        ON_CANARY(stack_end_canary_assign(stk, 0));
        stk->capacity /= resize_down_coeff;
    } else {
        return;
    }

    NOT_ON_CANARY(
        stack_elem_t *tmp_stk_ptr = (stack_elem_t *) realloc(stk->data, stk->capacity * sizeof(stack_elem_t));
        new_byte_size = stk->capacity * sizeof(stack_elem_t);
    )

    ON_CANARY(
        stack_elem_t *tmp_stk_ptr = (stack_elem_t *) realloc(stk->data, stk->capacity * sizeof(stack_elem_t) + 2 * CANARY_NMEMB);
        new_byte_size = stk->capacity * sizeof(stack_elem_t) + 2 * CANARY_NMEMB;
    )



    if (tmp_stk_ptr == NULL) {
        *return_err = ERR_REALLOC;
        DEBUG_ERROR(*return_err);
        return;
    }
    stk->data = tmp_stk_ptr;

    if (resize_up_state) {
        size_t old_capacity = stk->capacity / resize_up_coeff;
        stack_memset(stk->data + old_capacity, POISON_STACK_VALUE, old_capacity * (resize_up_coeff - 1));
    }

    ON_HASH(
        HASH_rebuild_ptr(stk, stk->data, new_byte_size);
    )

    ON_CANARY(
        stack_end_canary_assign(stk, CANARY_VALUE);
        CANARIES.canary_stk_right_ptr = stack_end_canary_getptr(stk);
    )
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

    ON_HASH(HASH_rebuild_value();)

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

    ON_HASH(HASH_rebuild_value();)

    return last_elem;

}
