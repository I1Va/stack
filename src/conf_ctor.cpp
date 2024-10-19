#include "conf_ctor.h"

void main_config_ctor(main_config_t *conf) {
    conf->exist = true;
    conf->log_file_stderr = false;
    return;
}

void main_config_dtor(main_config_t *conf) {
    *conf = {};
    return;
}

void auto_testing_config_ctor(auto_testing_config_t *conf) {
    conf->n_tests = 0;
    conf->exist = false;
    conf->log_file_stderr = false;
    return;
}

void auto_testing_config_dtor(auto_testing_config_t *conf) {
    *conf = {};
    return;
}
