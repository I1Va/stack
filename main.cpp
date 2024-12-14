#include <cstddef>
#include <stdlib.h>

#include "inc/general.h"
#include "stack_output.h"
#include "stack_funcs.h"
#include "stack_err_proc.h"

int main() {
    stk_err last_err = STK_ERR_OK;

    stack_t stk = {};
    // stack_init(&stk, 0, sizeof(int), &last_err, "", 12, "");

    STACK_INIT(&stk, 0, sizeof(int), stdout, &last_err);
    int a = 10;

    stack_push(&stk, &a, &last_err);
    int b = 22;

    DUMP(&stk, stdout, default_stk_elem_fprintf);

    // stack_get_elem(&stk, &b, 0, &last_err);
    stack_pop(&stk, &b, &last_err);

    printf("b = {%d}\n", b);

    DUMP(&stk, stdout, default_stk_elem_fprintf);
    // for (int i = 0; i < 5; i++) {
    //     printf("poped value: %d\n", *(int *)stack_get_elem(&stk, stk.size - 1, &last_err));
    //     stack_pop(&stk, &last_err);
    //     DUMP(&stk, stdout, default_stk_elem_fprintf);
    // }




    stack_destroy(&stk);

    return EXIT_SUCCESS;

}
