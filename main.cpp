#include <cstddef>
#include <stdlib.h>

#include "inc/general.h"
#include "inc/stack_output.h"
#include "stack_funcs.h"
#include "error_processing.h"

int main() {
    stk_err last_err = STK_ERR_OK;

    stack_t stk = {};
    // stack_init(&stk, 0, sizeof(int), &last_err, "", 12, "");

    STACK_INIT(&stk, 0, sizeof(int), stdout, &last_err);
    for (int i = 0; i < 5; i++) {
        int value = i * i + 52;
        printf("value: %d\n", value);
        stack_push(&stk, &value, &last_err);

    }
    DUMP(&stk, stdout);
    printf("b]b\\bb\\b\b\b\n\n\n");
    for (int i = 0; i < 5; i++) {
        printf("poped value: %d\n", *(int *)stack_get_elem(&stk, stk.size - 1, &last_err));
        stack_pop(&stk, &last_err);
        DUMP(&stk, stdout);
    }

    // printf("stack[3]: %d\n", stack_get_elem(&stk, 3, &last_err));
    // stack_assign_elem(&stk, 3, 525252);



    // stk_err last_err = STK_ERR_OK;

    // main_config_t main_config = {}; main_config_ctor(&main_config);

    // const size_t n_options = 3;
    // opt_data options[n_options] = {};

    // auto_testing_config_t auto_testing_config = {}; auto_testing_config_ctor(&auto_testing_config);
    // opt_data_ctor(&options[0], "-at-n_tests", "-auto_testing-n_tests", "%ld%s%f", &auto_testing_config.n_tests);
    // opt_data_ctor(&options[1], "-at-log_stderr", "-auto_testing-log_stderr", "%d", &auto_testing_config.log_file_stderr);
    // opt_data_ctor(&options[2], "-m-log_stderr", "-main-log_stderr", "%d", &main_config.log_file_stderr);
    // get_options(argc, argv, options, n_options);

    // printf("DONE\n");
    // // auto_testing_mode_launch(&auto_testing_config, &last_err);
    // // if (last_err != stk_err_OK) {
    // //     DEBUG_STK_ERROR(last_err)
    // //     CLEAR_MEMORY(exit_mark)
    // // }

    stack_destroy(&stk);

    return EXIT_SUCCESS;

}
