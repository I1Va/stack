#include "error_processing.h"
#include "general.h"
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
    // stk->size = 52;
    stack_push(stk, 52, &last_err);
    stack_push(stk, 12, &last_err);
    if (last_err != ERR_OK) {
        DEBUG_ERROR(last_err)
        CLEAR_MEMORY(exit_mark)
    }

    DUMP(stderr, stk)

    stack_destroy(stk);
    return EXIT_SUCCESS;

    exit_mark:

    if (stk != NULL) {
        stack_destroy(stk);
    }

    return EXIT_FAILURE;
}