#include "general.h"
#include "error_processing.h"
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>

typedef long long stack_elem_t;
#include "stack_funcs.h"

FILE *dump_output_file_ptr = stderr;

ON_HASH(

    void HASH_init(hash_t *HASH) {
        HASH->left_ptr = NULL;
        HASH->right_ptr = NULL;
        HASH->hash_mult = 257;
        HASH->hash_value = 0;
    }

    void HASH_print(hash_t *HASH) {
        printf("seg: [%p:%p)\n", HASH->left_ptr, HASH->right_ptr);
        printf("hash_value: [%llu]\n", HASH->hash_value);
        printf("get _value: [%llu]\n", HASH_get(HASH));
    }

    unsigned long long HASH_get(hash_t *HASH) {
        unsigned char *left_ptr = (unsigned char *) HASH->left_ptr;
        unsigned char *right_ptr = (unsigned char *) HASH->right_ptr;
        unsigned long long hash_value = 0;

        while (left_ptr < right_ptr) {
            hash_value += *left_ptr++ * HASH->hash_mult; // использую переполнение
        }

        return hash_value;
    }

    void HASH_rebuild_ptr(hash_t *HASH, char *left_ptr, char *right_ptr) {
        HASH->left_ptr = left_ptr;
        HASH->right_ptr = right_ptr;
    }

    void HASH_rebuild_value(hash_t *HASH) {
        HASH->hash_value = HASH_get(HASH);
    }

    bool HASH_check(hash_t *HASH) {
        return HASH->hash_value == HASH_get(HASH);
    }
)

ON_CANARY(
    canary_elem_t *stack_end_canary_getptr(stack_t *stk) {
        size_t stack_byte_size = stk->capacity * sizeof(stack_elem_t);
        char *canary_ptr = (char *) stk->data + stack_byte_size;
        unsigned long long alignment = (unsigned long long) canary_ptr % 8;
        canary_elem_t *canary_ptr_align = (canary_elem_t *) (canary_ptr + alignment); // FIXME: корявый нечитаемый padding fix. Придумать что-то по изящней
        return canary_ptr_align;
    }

    void stack_end_canary_assign(stack_t *stk, const canary_elem_t value) {
        canary_elem_t *canary_ptr = stack_end_canary_getptr(stk);
        *canary_ptr = value;
    }

    const size_t LEFT_CANARY_INDENT = (CANARY_NMEMB + sizeof(stack_elem_t) - 1) / sizeof(stack_elem_t);
)

void stack_memset(stack_elem_t *data, const stack_elem_t value, const size_t n) {
    for (size_t i = 0; i < n; i++) {
        *(data + i) = value;
    }
}

void ptr_stack_dump(FILE* stream, stack_t *stk) {
    fprintf(stream, RED "------------------------------------------------------------\n" WHT);
    fprintf(stream, GRN "_________stk: [%p:%p)" RED " | " WHT "bytes: %2lu\n" GRN, stk, stk + 1, sizeof(*stk));
    fprintf(stream, RED "------------------------------------------------------------\n" WHT);
    ON_HASH(
    fprintf(stream, "________HASH: [%p:%p)" RED " | " WHT "bytes: %2lu\n", &stk->HASH_STACK_STRUCT, &stk->HASH_STACK_STRUCT + 1, sizeof(stk->HASH_STACK_STRUCT));
    fprintf(stream, "________HASH: [%p:%p)" RED " | " WHT "bytes: %2lu\n", &stk->HASH_STACK_DATA, &stk->HASH_STACK_DATA + 1, sizeof(stk->HASH_STACK_DATA));
    )
    ON_CANARY(
    fprintf(stream, "_CANARY_LEFT: [%p:%p)" RED " | " WHT "bytes: %2lu\n", &stk->CANARY_LEFT, &stk->CANARY_LEFT + 1, sizeof(stk->CANARY_LEFT))
    fprintf(stream, "_CANARY_LEFT: [%p:%p)" RED " | " WHT "bytes: %2lu\n", &stk->CANARY_LEFT, &stk->CANARY_LEFT + 1, sizeof(stk->CANARY_LEFT))
    )
    fprintf(stream, "________size: [%p:%p)" RED " | " WHT "bytes: %2lu\n", &stk->size, &stk->size + 1, sizeof(stk->size));
    fprintf(stream, "____capacity: [%p:%p)" RED " | " WHT "bytes: %2lu\n", &stk->capacity, &stk->capacity + 1, sizeof(stk->capacity));
    ON_CANARY(
    fprintf(stream, "__CANARY_MID: [%p:%p)" RED " | " WHT "bytes: %2lu\n", &stk->CANARY_MID, &stk->CANARY_MID + 1, sizeof(stk->CANARY_MID));
    )
    fprintf(stream, "_______*data: [%p:%p)" RED " | " WHT "bytes: %2lu\n", &stk->data, &stk->data + 1, sizeof(stk->data));
    fprintf(stream, "__*born_file: [%p:%p)" RED " | " WHT "bytes: %2lu\n", &stk->born_file, &stk->born_file + 1, sizeof(stk->born_file));
    fprintf(stream, "__*born_line: [%p:%p)" RED " | " WHT "bytes: %2lu\n", &stk->born_line, &stk->born_line + 1, sizeof(stk->born_line));
    fprintf(stream, "__*born_func: [%p:%p)" RED " | " WHT "bytes: %2lu\n", &stk->born_func, &stk->born_func + 1, sizeof(stk->born_func));
    ON_CANARY(
    fprintf(stream, "CANARY_RIGHT: [%p:%p)" RED " | " WHT "bytes: %2lu\n", &stk->CANARY_RIGHT, &stk->CANARY_RIGHT + 1, sizeof(stl->CANARY_RIGHT))
    )
    fprintf(stream, RED "------------------------------------------------------------\n" WHT);
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
        ON_CANARY(
            canary_elem_t left_canary_val = *(canary_elem_t *)(stk->data - LEFT_CANARY_INDENT);
            fprintf_grn(dump_output_file_ptr, "[_left_canary] = %llx;\n", left_canary_val); //FIXME: %x? для unsigned long long работает?
        )
        for (size_t i = 0; i < stk->capacity; i++) {
            if (stk->data[i] == POISON_STACK_VALUE) {
                fprintf_grn(dump_output_file_ptr, "[%lu] = POISON;\n", i);
            } else {
                fprintf_grn(dump_output_file_ptr, "*[%lu] = %lld;\n", i, stk->data[i]);
            }
        }
        ON_CANARY(
            canary_elem_t right_canary_val = *stack_end_canary_getptr(stk);
            fprintf_grn(dump_output_file_ptr, "[right_canary] = %llx;\n", right_canary_val); //FIXME: %x? для unsigned long long работает?
        )
    }
    fprintf_wht(dump_output_file_ptr, "}\n");

    fprintf_wht(dump_output_file_ptr, "}\n");
}

err_code verify(stack_t *stk, err_code *return_err, const char *file_name, const char *func_name, const int line_idx) {
    ON_CANARY(
        if (*stk->CANARIES.canary_left_ptr != CANARY_VALUE) {
            *return_err = ERR_CANARY_LEFT;
            MY_ASSERT(ERR_CANARY_LEFT, abort())
        }
        if (*stk->CANARIES.canary_mid_ptr != CANARY_VALUE) {
            *return_err = ERR_CANARY_MID;
            MY_ASSERT(ERR_CANARY_MID, abort())
        }
        if (*stk->CANARIES.canary_right_ptr != CANARY_VALUE) {
            *return_err = ERR_CANARY_RIGHT;
            MY_ASSERT(ERR_CANARY_RIGHT, abort())
        }
        if (*stk->CANARIES.canary_stk_left_ptr != CANARY_VALUE) {
            *return_err = ERR_CANARY_STK_LEFT;
            MY_ASSERT(ERR_CANARY_STK_LEFT, abort())
        }
        if (*stk->CANARIES.canary_stk_right_ptr != CANARY_VALUE) {
            *return_err = ERR_CANARY_STK_RIGHT;
            MY_ASSERT(ERR_CANARY_STK_RIGHT, abort())
        }
    )

    ON_HASH(
        if (!HASH_check(&stk->HASH_STACK_STRUCT)) {
            HASH_print(&stk->HASH_STACK_STRUCT);
            *return_err = ERR_HASH_STACK_STRUCT_MISMATCH;
            MY_ASSERT(ERR_HASH_STACK_STRUCT_MISMATCH, return *return_err)
        }
        if (!HASH_check(&stk->HASH_STACK_DATA)) {
            HASH_print(&stk->HASH_STACK_DATA);
            *return_err = ERR_HASH_STACK_DATA_MISMATCH;
            MY_ASSERT(ERR_HASH_STACK_DATA_MISMATCH, return *return_err)
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

    if (stk->size > stk->capacity) {
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

    ON_CANARY(stk->CANARIES.canary_left_ptr = &stk->CANARY_LEFT;)
    ON_CANARY(stk->CANARIES.canary_mid_ptr = &stk->CANARY_MID;)
    ON_CANARY(stk->CANARIES.canary_right_ptr = &stk->CANARY_RIGHT;)

    stk->size = 0;
    stk->capacity = size;



    NOT_ON_CANARY(stk->data = (stack_elem_t *) calloc(stk->capacity, sizeof(stack_elem_t));)
    ON_CANARY    (stk->data = (stack_elem_t *) calloc(stk->capacity * sizeof(stack_elem_t) + 2 * CANARY_NMEMB + LEFT_CANARY_INDENT * sizeof(stack_elem_t), sizeof(char));)

    if (stk->data == NULL) {
        *return_err = ERR_CALLOC;
        DEBUG_ERROR(ERR_CALLOC)
        CLEAR_MEMORY(exit_mark)
    }

    ON_CANARY(
        stk->CANARIES.canary_stk_left_ptr = (canary_elem_t *) stk->data;
        *(canary_elem_t *) stk->data = CANARY_VALUE;
        stk->data += LEFT_CANARY_INDENT;
        stack_end_canary_assign(stk, CANARY_VALUE);
        stk->CANARIES.canary_stk_right_ptr = stack_end_canary_getptr(stk);
    )
    stack_memset(stk->data, POISON_STACK_VALUE, stk->capacity);

    stk->born_file = born_file;
    stk->born_line = born_line;
    stk->born_func = born_func;

    ON_HASH(
        stk->HASH_STACK_STRUCT = {}; HASH_init(&stk->HASH_STACK_STRUCT);
        stk->HASH_STACK_DATA = {}; HASH_init(&stk->HASH_STACK_DATA);
        HASH_rebuild_ptr(&stk->HASH_STACK_STRUCT, (char *) &stk->size, (char *) (&stk->born_func + 1));
        HASH_rebuild_ptr(&stk->HASH_STACK_DATA, (char *) stk->data, ((char *) stk->data + stk->capacity * sizeof(stack_elem_t)));

        HASH_rebuild_value(&stk->HASH_STACK_STRUCT);
        HASH_rebuild_value(&stk->HASH_STACK_DATA);
    )


    return;

    exit_mark:
    ON_CANARY(
        if (stk->data != NULL) {
            stk->data -= LEFT_CANARY_INDENT;
        }
    )

    if (stk->data != NULL) {
        FREE(stk->data);
    }

    return;
}

void stack_destroy(stack_t *stk) {
    ON_CANARY(
        if (stk->data != NULL) {
            stk->data -= LEFT_CANARY_INDENT;
        }
    )

    FREE(stk->data);
}

void resize(stack_t *stk, err_code *return_err) {
    assert(stk != NULL);
    assert(return_err != NULL);

    bool resize_up_state = false;
    bool unit_length_state = false;
    size_t new_byte_size = 0;

    if (stk->capacity == 0) {
        ON_CANARY(stack_end_canary_assign(stk, 0));
        stk->capacity++;
        unit_length_state = true;
    } else if (stk->size + 1 >= stk->capacity) {
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
        stk->data = (stack_elem_t *) realloc(stk->data, stk->capacity * sizeof(stack_elem_t));
        new_byte_size = stk->capacity * sizeof(stack_elem_t);
    )

    ON_CANARY(
        stk->data -= LEFT_CANARY_INDENT;
        stk->data = (stack_elem_t *) realloc(stk->data, stk->capacity * sizeof(stack_elem_t) + 2 * CANARY_NMEMB + LEFT_CANARY_INDENT * sizeof(stack_elem_t));
        stk->data += LEFT_CANARY_INDENT;
        new_byte_size = stk->capacity * sizeof(stack_elem_t) + 2 * CANARY_NMEMB + LEFT_CANARY_INDENT * sizeof(stack_elem_t);
    )

    if (stk->data == NULL) {
        *return_err = ERR_REALLOC;
        DEBUG_ERROR(*return_err);
        return;
    }


    if (resize_up_state) {
        size_t old_capacity = stk->capacity / resize_up_coeff;
        stack_memset(stk->data + old_capacity, POISON_STACK_VALUE, old_capacity * (resize_up_coeff - 1));
    }
    if (unit_length_state) {
        stack_memset(stk->data, POISON_STACK_VALUE, 1);
    }

    ON_HASH(
        HASH_rebuild_ptr(&stk->HASH_STACK_DATA, (char *) stk->data, (char *) stk->data + new_byte_size);
    )
    ON_CANARY(
        stack_end_canary_assign(stk, CANARY_VALUE);
        stk->CANARIES.canary_stk_right_ptr = stack_end_canary_getptr(stk);
        stk->CANARIES.canary_stk_left_ptr = (canary_elem_t *) (stk->data - LEFT_CANARY_INDENT);
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

    ON_HASH(HASH_rebuild_value(&stk->HASH_STACK_STRUCT);)
    ON_HASH(HASH_rebuild_value(&stk->HASH_STACK_DATA);)

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
    stk->data[stk->size] = POISON_STACK_VALUE;

    ON_HASH(HASH_rebuild_value(&stk->HASH_STACK_STRUCT);)
    ON_HASH(HASH_rebuild_value(&stk->HASH_STACK_DATA);)

    return last_elem;
}

stack_elem_t stack_get_last(stack_t *stk, err_code *return_err) {
    assert(stk != NULL);

    VERIFY(stk, return_err, )

    if (stk->size == 0) {
        *return_err = ERR_STACK_LAST_ELEM;
        DEBUG_ERROR(*return_err)
        return POISON_STACK_VALUE;
    }

    return stk->data[stk->size - 1];
}
