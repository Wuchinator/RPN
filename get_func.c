#include "get_func.h"

char *input_func(int *flag) {
    char *function = NULL;
    int start_size = 0;
    int extended_size = 0;
    do {
        if (extended_size == start_size) {
            function = extending_func(function, &start_size, flag);
        }
        function[extended_size] = getchar();
    } while ('\n' != function[extended_size++] && 0 == *flag);
    function[extended_size - 1] = '\0';
    return function;
}

char *extending_func(char *function, int *start_size, int *flag) {
    char *tmp_exp = function;
    if (*start_size) {
        *start_size = (int)((double)*start_size * 2);
    } else {
        *start_size = 32;
    }
    tmp_exp = realloc(tmp_exp, *start_size * sizeof(char));
    if (NULL == tmp_exp) {
        *flag = 1;
    } else {
        function = tmp_exp;
    }
    return function;
}
