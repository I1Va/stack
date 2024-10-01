#include "conf_ctor.h"
#include "error_processing.h"

#include <cstdlib>

void main_launch_config_ctor(main_launch_config_t *conf) {
    if (conf) {}
    return;
}

void main_launch_config_dtor(main_launch_config_t *conf) {
    *conf = {};
    return;
}
