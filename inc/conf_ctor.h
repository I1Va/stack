#ifndef CONF_CTOR_H
#define CONF_CTOR_H

struct main_launch_config_t {
    bool exist = true;
    
};

void main_launch_config_ctor(main_launch_config_t *conf);

void main_launch_config_dtor(main_launch_config_t *conf);

#endif // CONF_CTOR_H