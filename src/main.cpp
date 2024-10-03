#include <cstdarg>
#include <cstddef>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "error_processing.h"
#include "args_proc.h"
#include "conf_ctor.h"
#include "general.h"


int main(const int argc, const char *argv[]) {
    err_code last_err = ERR_OK;

    main_config_t main_config = {};
    main_config_ctor(&main_config);

    auto_testing_config_t auto_testing_config;
    const size_t n_options = 1;
    opt_data options[n_options] = {};
    // opt_data_ctor(&options[0], "-t@n_tests=", "-testing@n_tests", "%ld", )
    get_options(argc, argv, options, n_options);

    // config_state mode_launcher_list =
    // {
    //     {}
    // }
    // TODO: написать mode_launcher. Если config.exist = true, то вызывает функцию по указателю в структуре config

    main_testing_mode_launch(&main_config, &last_err);
    if (last_err != ERR_OK) {
        DEBUG_ERROR(last_err)
        CLEAR_MEMORY(exit_mark)
    }



    return EXIT_SUCCESS;

    exit_mark:

    return EXIT_FAILURE;
}
