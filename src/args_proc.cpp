#include <cstddef>
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
    *option = {};
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

            sscanf(value + 1, (ptr->fmt), ptr->val_ptr); // FIXME: исправить warning. Мб использовать __atribute__
        }
    }
}

void main_testing_mode_launch(main_config_t *conf, err_code *return_err) {

    assert(conf != NULL);
    assert(return_err != NULL);

    if (!conf->exist) {
        return;
    }

    err_code last_err = ERR_OK;

    stack_t stk = {};





    

    stack_destroy(&stk);

    return;
}

void auto_testing_mode_launch(auto_testing_config_t *conf, err_code *return_err) {

}
void main_mode_launch(main_config_t *conf, err_code *return_err) {
    assert(conf != NULL);
    assert(return_err != NULL);

    printf("THERE IS SHOULD BE MAIN MODE");
}
