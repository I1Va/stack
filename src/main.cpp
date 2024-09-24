#include "error_processing.h"
#include "general.h"
#include <cstdlib>
typedef int stack_elem_t;
#include "stack_funcs.h"

int main() {
    // err_code last_err = ERR_OK;

    stack_t *stk = stack_init(10);
    if (stk == NULL) {
        DEBUG_ERROR(ERR_INIT)
        CLEAR_MEMORY(exit_mark)

    }

    stack_destroy(stk);
    return EXIT_SUCCESS;

    exit_mark:

    if (stk != NULL) {
        stack_destroy(stk);
    }

    return EXIT_FAILURE;
}