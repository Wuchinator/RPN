#include "stack.h"

stack *init() {
    stack *stack_of_tokens = malloc(sizeof(stack));
    if (NULL != stack_of_tokens) {
        stack_of_tokens->size = 0;
        stack_of_tokens->top = NULL;
    }
    return stack_of_tokens;
}

void push(stack *stack_of_tokens, token value) {
    node *next_node = malloc(sizeof(node));
    if (NULL != next_node) {
        next_node->data = value;
        next_node->next = stack_of_tokens->top;
        stack_of_tokens->top = next_node;
        stack_of_tokens->size++;
    }
}

token pop(stack *stack_of_tokens) {
    token extended = {.type = 0, .int_value = 0};
    if (stack_of_tokens->top) {
        extended = stack_of_tokens->top->data;
        node *pulled_out = stack_of_tokens->top;
        stack_of_tokens->top = stack_of_tokens->top->next;
        stack_of_tokens->size--;
        free(pulled_out);
    }
    return extended;
}

void destroy(stack *stack_of_tokens) {
    node *current_node = NULL;
    while (NULL != stack_of_tokens->top) {
        current_node = stack_of_tokens->top;
        stack_of_tokens->top = stack_of_tokens->top->next;
        free(current_node);
    }
    free(stack_of_tokens);
}