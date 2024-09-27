#include <cstdlib>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "conf_ctor.h"
#include "general.h"
#include "error_processing.h"

typedef int stack_elem_t;
#include "stack_funcs.h"

#include "general.h"

#include "args_proc.h"

void opt_data_ctor(opt_data *option, const char *const short_name_src, const char *const long_name_src,
    const char *const fmt_src, void *val_ptr_src) {

    option->short_name = short_name_src;
    option->long_name = long_name_src;
    option->fmt = fmt_src;

    option->val_ptr = val_ptr_src;
    option->exist = false;
}

void opt_data_dtor(opt_data *option) {
    option = NULL; // FIXME: создается копия указателя и option = NULL в рамках блока opt_data_dtor
    return;
}

opt_data *option_list_ptr(const char *name, opt_data opts[], const size_t n_opts) {
    for (size_t i = 0; i < n_opts; i++) {
        if (strcmp(name, opts[i].short_name) == 0 || strcmp(name, opts[i].long_name) == 0) {
            return &opts[i];
        }
    }
    return NULL;
}

void get_options(const int argc, const char* argv[], opt_data opts[], const size_t n_opts) {
    assert(argc >= 0);

    for (int i = 1; i < argc; i++) {
        char name[max_opt_name_sz];
        char value[max_opt_name_sz];
        sscanf(argv[i], "%[^=]%s", name, value);

        opt_data *ptr = option_list_ptr(name, opts, n_opts);

        if (ptr != NULL) {
            ptr->exist = true;

            sscanf(value + 1, (ptr->fmt), ptr->val_ptr);
        }
    }
}

void main_mode_launch(main_launch_config_t *conf, err_code *return_err) {
    err_code last_err = ERR_OK;

    stack_t stk = {};
    STACK_INIT(&stk, 10, &last_err)
    if (last_err != ERR_OK) {
        *return_err = last_err;
        DEBUG_ERROR(ERR_INIT)
        CLEAR_MEMORY(exit_mark)
    }

    for (stack_elem_t i = 0; i < 100; i++) {
        stack_push(&stk, i, &last_err);
        DUMP(&stk)
        fprintf(stderr, "\n\n");
        if (last_err != ERR_OK) {
            *return_err = last_err;
            DEBUG_ERROR(last_err);
            CLEAR_MEMORY(exit_mark);
        }
    }

    for (stack_elem_t i = 30; i >= 1; i--) {
        stack_pop(&stk, &last_err);
        DUMP(&stk)
        fprintf(stderr, "\n\n");
        if (last_err != ERR_OK) {
            *return_err = last_err;
            DEBUG_ERROR(last_err);
            CLEAR_MEMORY(exit_mark);
        }
    }

    stack_destroy(&stk);

    return;

    exit_mark:

    stack_destroy(&stk);

    return;
}
