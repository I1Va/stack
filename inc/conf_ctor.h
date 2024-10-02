#ifndef CONF_CTOR_H
#define CONF_CTOR_H

#include <string.h>

struct main_config_t {
    bool exist = true;
};

struct auto_testing_config_t {
    bool exist;
    size_t n_tests;
};

void main_config_ctor(main_config_t *conf);

void main_config_dtor(main_config_t *conf);

void auto_testing_config_ctor(auto_testing_config_t *conf);

void auto_testing_config_dtor(auto_testing_config_t *conf);

#endif // CONF_CTOR_H