#include "parser.h"

token *parse(char *function, int *flag, int *tokens_size_ptr) {
    int count_operators = 1;
    token *tokens = NULL;
    int tokens_size = 0;
    int tokens_max_size = 0;
    int count_parenthesis = 0;
    while (*function && 0 == *flag) {
        if (tokens_size == tokens_max_size) {
            tokens = token_extending(tokens, &tokens_max_size, flag);
        }
        if (*function == ' ') {
        } else if (*function >= '0' && *function <= '9') {
            tokens[tokens_size++] = getter_number(&function, flag);
            count_operators--;
        } else if (*function == '(') {
            token new_token = {.type = OPERATOR, .int_value = left_parenthesis, .priority = 0};
            tokens[tokens_size++] = new_token;
            count_parenthesis++;
        } else if (*function == ')') {
            token new_token = {.type = OPERATOR, .int_value = right_parenthesis, .priority = 0};
            tokens[tokens_size++] = new_token;
            count_parenthesis--;
        } else if (*function == 'x') {
            token new_token = {.type = VAR};
            tokens[tokens_size++] = new_token;
            count_operators--;
        } else if (1 == count_operators) {
            tokens[tokens_size++] = uno_opers(&function, flag);
        } else if (0 == count_operators) {
            tokens[tokens_size++] = bin_opers(function, flag);
            count_operators++;
        }
        if (count_parenthesis < 0 || (count_operators != 0 && count_operators != 1)) {
            *flag = 1;
        }
        function++;
    }
    if (0 != count_parenthesis || count_operators != 0) {
        *flag = 1;
    }
    *tokens_size_ptr = tokens_size;
    return tokens;
}

token uno_opers(char **function, int *flag) {
    token uno_tokens_operation = {.type = OPERATOR};
    if (**function == '-') {
        uno_tokens_operation.int_value = uno_minus;
    } else if (**function == 's') {
        if (strncmp(*function, "sin(", 4) == 0) {
            uno_tokens_operation.int_value = SIN;
            *function += 2;
        } else if (0 == strncmp(*function, "sqrt(", 5)) {
            uno_tokens_operation.int_value = SQRT;
            *function += 3;
        } else {
            *flag = 1;
        }
    } else if (**function == 'c') {
        if (strncmp(*function, "cos(", 4) == 0) {
            uno_tokens_operation.int_value = COS;
            *function += 2;
        } else if (strncmp(*function, "ctg(", 4) == 0) {
            uno_tokens_operation.int_value = CTG;
            *function += 2;
        } else {
            *flag = 1;
        }
    } else if (strncmp(*function, "tan(", 4) == 0) {
        uno_tokens_operation.int_value = TAN;
        *function += 2;
    } else if (strncmp(*function, "ln(", 3) == 0) {
        uno_tokens_operation.int_value = ln;
        *function += 1;
    } else {
        *flag = 1;
    }
    return uno_tokens_operation;
}

token bin_opers(const char *function, int *flag) {
    token binary_tokens_operation = {.type = OPERATOR};
    if (*function == '-') {
        binary_tokens_operation.int_value = minus;
        binary_tokens_operation.priority = 1;
    } else if (*function == '+') {
        binary_tokens_operation.int_value = plus;
        binary_tokens_operation.priority = 1;
    } else if (*function == '/') {
        binary_tokens_operation.int_value = div;
        binary_tokens_operation.priority = 2;
    } else if (*function == '*') {
        binary_tokens_operation.int_value = mult;
        binary_tokens_operation.priority = 2;
    } else {
        *flag = 1;
    }
    return binary_tokens_operation;
}

token *token_extending(token *tokens, int *tokens_max_size, int *flag) {
    token *temp_tokens = tokens;
    if (*tokens_max_size) {
        *tokens_max_size = (int)((double)*tokens_max_size * 2);
    } else {
        *tokens_max_size = 8;
    }
    temp_tokens = realloc(temp_tokens, *tokens_max_size * sizeof(token));
    if (temp_tokens == NULL) {
        *flag = 1;
    } else {
        tokens = temp_tokens;
    }
    return tokens;
}

token getter_number(char **function, int *flag) {
    char *end_of_line_ptr = *function;
    int dot_count = 0;
    token number_token = {.type = NUMBER, .double_value = 0., .priority = 0};
    while ((*end_of_line_ptr >= '0' && *end_of_line_ptr <= '9') || *end_of_line_ptr == '.') {
        if (*end_of_line_ptr == '.') {
            dot_count++;
        }
        end_of_line_ptr++;
    }
    if (dot_count > 1 || *(end_of_line_ptr - 1) == '.') {
        *flag = 1;
    } else {
        char previous_char = *end_of_line_ptr;
        *end_of_line_ptr = '\0';
        double number = atof(*function);
        *end_of_line_ptr = previous_char;
        number_token.double_value = number;
    }
    *function = end_of_line_ptr - 1;
    return number_token;
}