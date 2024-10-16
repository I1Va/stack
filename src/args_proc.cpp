#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "conf_ctor.h"
#include "general.h"
#include "error_processing.h"
#include "output.h"

typedef long long stack_elem_t;
#include "stack_funcs.h"

#include "general.h"

#include "args_proc.h"

void opt_data_ctor(opt_data *option, const char *const short_name_src, const char *const long_name_src,
    const char *const fmt_src, void *val_ptr_src) {

    option->short_name = short_name_src;
    option->long_name = long_name_src;
    option->fmt = fmt_src;

    option->val_ptr = val_ptr_src;
    option->exist = true;
}

void opt_data_dtor(opt_data *option) {
    *option = {};
    return;
}

opt_data *option_list_ptr(const char *name, opt_data opts[], const size_t n_opts) {
    for (size_t i = 0; i < n_opts; i++) {
        if (!opts[i].exist) {
            continue;
        }
        if (strcmp(name, opts[i].short_name) == 0) {
            return &opts[i];
        }
        if (strcmp(name, opts[i].long_name) == 0) {
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
            sscanf(value + 1, (ptr->fmt), ptr->val_ptr); // FIXME: исправить warning. Мб использовать __atribute__
            ptr->exist = true;
        }
    }
}

stack_elem_t stack_elem_from_str(const char str[], const size_t n) {
    char *elem_1 = (char *) calloc(n * 2, sizeof(char));
    char *start_elem_1 = elem_1;

    for (size_t idx = 0; idx < n; idx++) {
        *(elem_1 + idx) = str[idx];
    }

    stack_elem_t stack_elem_1 = *((stack_elem_t *) start_elem_1);
    FREE(elem_1);

    return stack_elem_1;
}

void breaking_test_launch(main_config_t *conf, unsigned long long *return_err) {
    assert(conf != NULL);
    assert(return_err != NULL);
    // Строки туэ морса
    char string_1[] = "edHsfEHs";
    char string_2[] = "fEHsedHs";
    // stk1 = {"edHs", "fEHs"}
    // stk2 = {"fEHs", "edHs"}
    // hash(stk1) == hash(stk2);

    hash_t hash1 = {};
    hash1.hash_mult = 257;
    hash1.hash_value= 0;
    hash1.left_ptr = string_1;
    hash1.right_ptr = string_1 + sizeof(string_1);

    hash_t hash2 = {};
    hash2.hash_mult = 257;
    hash2.hash_value = 0;
    hash2.left_ptr = string_2;
    hash2.right_ptr = string_2 + sizeof(string_2);


    printf("hash1: %llu\n", HASH_get(&hash1));
    printf("hash2: %llu\n", HASH_get(&hash2));

    unsigned long long last_err = ERR_OK;
    stack_t stk = {};
    STACK_INIT(&stk, 0, &last_err);

    char string_1_part_1[] = "edHs";
    char string_1_part_2[] = "fEHs";
    stack_elem_t elem_1 = stack_elem_from_str(string_1_part_1, 4);
    stack_elem_t elem_2 = stack_elem_from_str(string_1_part_2, 4);

    stack_push(&stk, elem_1 , &last_err);
    stack_push(&stk, elem_2, &last_err);
    HASH_print(&stk.HASH_STACK_DATA);
    DUMP(&stk);
    *(stk.data) = 0;
    *(stk.data + 1) = 0;
    // VERIFY(&stk, &last_err, abort())
    DUMP(&stk);
    *(stk.data) = elem_2;
    *(stk.data + 1) = elem_1;
    HASH_print(&stk.HASH_STACK_DATA);
    DUMP(&stk);

    VERIFY(&stk, &last_err, abort())
    stack_destroy(&stk);
}

void main_testing_mode_launch(main_config_t *conf, unsigned long long *return_err) {
    // breaking_test_launch(conf, return_err);
    unsigned long long last_err = ERR_OK;

    char log_path[] = "./logs/log.txt";
    if (!conf->log_file_stderr) {
        log_init(log_path, &last_err);
    } else {
        log_init(NULL, &last_err);
    }


    stack_t stk = {}; STACK_INIT(&stk, 14, return_err)
    DUMP(&stk)

    last_err |= ERR_CANARY_MID;
    last_err |= ERR_STACK_LAST_ELEM;
    last_err |= ERR_ARGS;
    last_err |= ERR_MEM;

    LogErr(LOG_ERROR, last_err)

    last_err = ERR_OK;

    DEBUG_ERROR(last_err)


    DUMP(&stk)


    for (size_t i = 0; i < 10; i++) {
        stack_push(&stk, rand(), &last_err);
        if (last_err != ERR_OK) {
            DEBUG_ERROR(last_err)
            CLEAR_MEMORY(exit_mark)
        }
    }
    DUMP(&stk)
    LogStkPtrInfo(LOG_ANALYS, &stk)
    for (size_t i = 0; i < 10; i++) {
        stack_pop(&stk, &last_err);
        if (last_err != ERR_OK) {
            DEBUG_ERROR(last_err)
            CLEAR_MEMORY(exit_mark)
        }
    }

    DUMP(&stk);


    LogStkPtrInfo(LOG_DEBUG, &stk)

    stack_destroy(&stk);
    return;

    exit_mark:

    return;
}


void auto_testing_mode_launch(auto_testing_config_t *conf, unsigned long long *return_err) {
    assert(conf != NULL);
    if (!conf->n_tests) {
        return;
    }

    assert(return_err != NULL);


    unsigned long long last_err = ERR_OK;

    char log_path[] = "./logs/log.txt";

    const char input_path[] = "src/testing/input.txt";
    const char create_test_command[] = "python3 src/testing/test_gen.py > src/testing/input.txt";
    const char create_answer_command[] = "python3 src/testing/brut.py < src/testing/input.txt > src/testing/answer.txt";
    const char output_path[] = "src/testing/output.txt";

    FILE* output_file = NULL;
    FILE* input_file = NULL;
    size_t n_input_coms = 0;

    stack_t stk = {};

    if (conf->log_file_stderr) {
        log_init(log_path, &last_err);
    } else {
        log_init(NULL, &last_err);
    }
    if (last_err != ERR_OK) {
        DEBUG_ERROR(last_err);
        CLEAR_MEMORY(exit_mark)
    }

    STACK_INIT(&stk, 0, &last_err)

    if (system(create_test_command)) {
        *return_err |= ERR_SYSTEM;
        DEBUG_ERROR(*return_err)
        CLEAR_MEMORY(exit_mark)
    }

    if (system(create_answer_command)) {
        *return_err |= ERR_SYSTEM;
        DEBUG_ERROR(*return_err)
        CLEAR_MEMORY(exit_mark)
    }

    input_file = fopen(input_path, "r");
    if (input_file == NULL) {
        *return_err |= ERR_FILE_OPEN;
        DEBUG_ERROR(*return_err)
        CLEAR_MEMORY(exit_mark)
    }

    output_file = fopen(output_path, "w");
    if (output_file == NULL) {
        *return_err = ERR_FILE_OPEN;
        DEBUG_ERROR(*return_err)
        CLEAR_MEMORY(exit_mark)
    }
    for (size_t test_idx = 0; test_idx < conf->n_tests; test_idx++) {
        fscanf(input_file, "%lu", &n_input_coms);
        for (size_t com_idx = 0; com_idx < n_input_coms; com_idx++) {
            char com_str[10] = {};
            long long com_val = 0;

            fscanf(input_file, "%s", com_str);
            // printf_grn("cur command: %s\n", com_str);
            DUMP(&stk);

            LogErr(LOG_ERROR, last_err);
            if (strcmp(com_str, "push") == 0) {
                fscanf(input_file, "%lld", &com_val);
                stack_push(&stk, com_val, return_err);
            } else if (strcmp(com_str, "pop") == 0) {
                stack_pop(&stk, &last_err);
                if (last_err != ERR_OK) {
                    fprintf(output_file, "pop_error\n");
                }
            } else if (strcmp(com_str, "last") == 0) {
                stack_elem_t last_elem = stack_get_last(&stk, &last_err);
                if (last_err != ERR_OK) {
                    fprintf(output_file, "last_error\n");
                } else {
                    fprintf(output_file, "%lld\n", last_elem);
                }
            } else {
                assert(1);
            }
            last_err = ERR_OK; // спефика авто тестинга. Предыдущие ошибки должны быть аннулированы, чтобы не перетирать будущие
        }
        if (!system("diff src/testing/output.txt src/testing/answer.txt")) {
            debug("dismatch");
            abort();
        }
    }




    stack_destroy(&stk);

    fclose(input_file);
    fclose(output_file);

    return;

    exit_mark:

    stack_destroy(&stk);
    if (input_file != NULL) {
        fclose(input_file);
    }
    if (output_file != NULL) {
        fclose(output_file);
    }
    return;
}

void main_mode_launch(main_config_t *conf, unsigned long long *return_err) {
    assert(conf != NULL);
    assert(return_err != NULL);
}
