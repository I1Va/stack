#include <stdlib.h>

#include "error_processing.h"
#include "args_proc.h"
#include "conf_ctor.h"
#include "general.h"

int main(const int argc, const char *argv[]) {
    stk_err last_err = STK_ERR_OK;

    main_config_t main_config = {}; main_config_ctor(&main_config);

    const size_t n_options = 3;
    opt_data options[n_options] = {};

    auto_testing_config_t auto_testing_config = {}; auto_testing_config_ctor(&auto_testing_config);
    opt_data_ctor(&options[0], "-at-n_tests", "-auto_testing-n_tests", "%ld%s%f", &auto_testing_config.n_tests);
    opt_data_ctor(&options[1], "-at-log_stderr", "-auto_testing-log_stderr", "%d", &auto_testing_config.log_file_stderr);
    opt_data_ctor(&options[2], "-m-log_stderr", "-main-log_stderr", "%d", &main_config.log_file_stderr);
    get_options(argc, argv, options, n_options);

    // auto_testing_mode_launch(&auto_testing_config, &last_err);
    // if (last_err != stk_err_OK) {
    //     DEBUG_ERROR(last_err)
    //     CLEAR_MEMORY(exit_mark)
    // }

    main_testing_mode_launch(&main_config, &last_err);
    if (last_err != STK_ERR_OK) {
        DEBUG_ERROR(last_err)
        CLEAR_MEMORY(exit_mark)
    }

    return EXIT_SUCCESS;

    exit_mark:

    return EXIT_FAILURE;
}
