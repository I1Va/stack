#include "error_processing.h"
#include "general.h"
#include <cstddef>
#include <cstdlib>

typedef int stack_elem_t;
#include "stack_funcs.h"

int main() {
    err_code last_err = ERR_OK;

    stack_t *stk = INIT(10)
    if (stk == NULL) {
        DEBUG_ERROR(ERR_INIT)
        CLEAR_MEMORY(exit_mark)

    }

    for (stack_elem_t i = 0; i < 30; i++) {
        stack_push(stk, i, &last_err);
        DUMP(stderr, stk)
        fprintf(stderr, "\n\n");
        if (last_err != ERR_OK) {
            DEBUG_ERROR(last_err);
            CLEAR_MEMORY(exit_mark);
        }

    }
    for (stack_elem_t i = 30; i >= 0; i--) {
        stack_pop(stk, &last_err);
        DUMP(stderr, stk)
        fprintf(stderr, "\n\n");
        if (last_err != ERR_OK) {
            DEBUG_ERROR(last_err);
            CLEAR_MEMORY(exit_mark);
        }
    }

    stack_destroy(stk);
    return EXIT_SUCCESS;

    exit_mark:

    if (stk != NULL) {
        stack_destroy(stk);
    }

    return EXIT_FAILURE;
}