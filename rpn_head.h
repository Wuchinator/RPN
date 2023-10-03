#ifndef RPN_CALC
#define RPN_CALC
#include "stack.h"

token *convert_rpn(token *tokens, int tokens_size, int *rpn_tokens_size);

int handler(stack *op_stack, token or_token, int current_token, token *rpn_tokens, int *rpn_tokens_size);

double calc(token *rpn_tokens, int rpn_tokens_size, double x_value);

void uno_oper(stack *operand_stack, int operator_value);

void bin_oper(stack *operand_stack, int operator_value);

#endif