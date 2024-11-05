#include "inc/general.h"
#include "inc/stack_output.h"
#include <stdlib.h>

typedef int stack_elem_t;
#include "stack_funcs.h"
#include "error_processing.h"

int main(const int argc, const char *argv[]) {


    stk_err last_err = STK_ERR_OK;
    log_init(NULL, &last_err);

    stack_t stk = {};
    STACK_INIT(&stk, 0, &last_err);

    for (int i = 0; i < 10; i++) {
        stack_push(&stk, i * i + 52, &last_err);
    }

    printf("stack[3]: %d\n", stack_get_elem(&stk, 3, &last_err));
    stack_assign_elem(&stk, 3, 525252);
    DUMP(&stk);


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
    // //     DEBUG_ERROR(last_err)
    // //     CLEAR_MEMORY(exit_mark)
    // // }

    return EXIT_SUCCESS;

}
