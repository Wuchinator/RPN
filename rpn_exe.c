#include "rpn_head.h"

token *convert_rpn(token *tokens, int tokens_size, int *rpn_tokens_size) {
    stack *operator_stack = init();
    token *rpn_tokens = malloc(tokens_size * sizeof(token));
    int current_token = 0;
    for (int i = 0; i < tokens_size; i++) {
        if (NUMBER == tokens[i].type || VAR == tokens[i].type) {
            rpn_tokens[current_token++] = tokens[i];
        } else {
            current_token = handler(operator_stack, tokens[i], current_token, rpn_tokens, rpn_tokens_size);
        }
    }
    while (operator_stack->top) {
        rpn_tokens[current_token++] = pop(operator_stack);
    }
    destroy(operator_stack);
    return rpn_tokens;
}

int handler(stack *stack_of_operators, token argument_for_operators, int current_token, token *rpn_tokens,
            int *rpn_tokens_size) {
    if (argument_for_operators.int_value > 4) {
        push(stack_of_operators, argument_for_operators);
    } else if (argument_for_operators.int_value != 4) {
        while (stack_of_operators->top &&
               (stack_of_operators->top->data.int_value > 5 ||
                (stack_of_operators->top->data.int_value < 4 &&
                 stack_of_operators->top->data.priority >= argument_for_operators.priority))) {
            rpn_tokens[current_token++] = pop(stack_of_operators);
        }
        push(stack_of_operators, argument_for_operators);
    } else {
        while (stack_of_operators->top && stack_of_operators->top->data.int_value != left_parenthesis) {
            rpn_tokens[current_token++] = pop(stack_of_operators);
        }
        pop(stack_of_operators);
        *rpn_tokens_size -= 2;
    }
    return current_token;
}

void uno_oper(stack *operand_stack, int operator_value) {
    token operand_token = pop(operand_stack);
    token updated_token = {.type = NUMBER, .double_value = 0., .priority = 0};
    if (uno_minus == operator_value) {
        updated_token.double_value = -1 * operand_token.double_value;
    } else if (operator_value == SIN) {
        updated_token.double_value = sin(operand_token.double_value);
    } else if (operator_value == COS) {
        updated_token.double_value = cos(operand_token.double_value);
    } else if (operator_value == TAN) {
        updated_token.double_value = tan(operand_token.double_value);
    } else if (operator_value == CTG) {
        updated_token.double_value = 1.0 / tan(operand_token.double_value);
    } else if (operator_value == SQRT) {
        updated_token.double_value = sqrt(operand_token.double_value);
    } else if (operator_value == ln) {
        updated_token.double_value = log(operand_token.double_value);
    }
    push(operand_stack, updated_token);
}

void bin_oper(stack *operand_stack, int operator_value) {
    token right_operand = pop(operand_stack);
    token left_operand = pop(operand_stack);
    token result_token = {.type = NUMBER, .double_value = 0.0, .priority = 0};
    if (operator_value == plus) {
        result_token.double_value = left_operand.double_value + right_operand.double_value;
    } else if (operator_value == minus) {
        result_token.double_value = left_operand.double_value - right_operand.double_value;
    } else if (operator_value == mult) {
        result_token.double_value = left_operand.double_value * right_operand.double_value;
    } else if (operator_value == div) {
        result_token.double_value = left_operand.double_value / right_operand.double_value;
    }
    push(operand_stack, result_token);
}

double calc(token *rpn_tokens, int rpn_tokens_size, double var_value) {
    stack *operand_stack = init();
    for (int i = 0; i < rpn_tokens_size; i++) {
        if (NUMBER == rpn_tokens[i].type) {
            push(operand_stack, rpn_tokens[i]);
        } else if (VAR == rpn_tokens[i].type) {
            token var_token = {.type = NUMBER, .double_value = var_value, .priority = 0};
            push(operand_stack, var_token);
        } else if (rpn_tokens[i].int_value > 4) {
            uno_oper(operand_stack, rpn_tokens[i].int_value);
        } else {
            bin_oper(operand_stack, rpn_tokens[i].int_value);
        }
    }
    token result_token = pop(operand_stack);
    destroy(operand_stack);
    return result_token.double_value;
}