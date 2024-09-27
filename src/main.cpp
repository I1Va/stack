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
    main_launch_config_t main_launch_config = {};
    main_launch_config_ctor(&main_launch_config);

    const size_t n_options = 0;
    opt_data options[n_options];
    get_options(argc, argv, options, n_options);

    main_mode_launch(&main_launch_config);
}