#include "conf_ctor.h"
#include "error_processing.h"

#include <cstdlib>

void main_launch_config_ctor(main_launch_config_t *conf) {
    conf->canary = false;
    conf->hashes = false;
    conf->duplication = false;
}

void main_launch_config_dtor(main_launch_config_t *conf) {
    *conf = {};
    return;
}
