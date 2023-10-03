#ifndef STACK
#define STACK
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER 0
#define OPERATOR 1
#define VAR 2

#define plus 0
#define minus 1
#define mult 2
#define div 3
#define right_parenthesis 4
#define left_parenthesis 5
#define uno_minus 6
#define SIN 7
#define COS 8
#define TAN 9
#define CTG 10
#define SQRT 11
#define ln 12

typedef struct token {
    int type;
    union {
        int int_value;
        double double_value;
    };
    int priority;
} token;

typedef struct node {
    token data;
    struct node *next;
} node;

typedef struct stack {
    int size;
    node *top;
} stack;

stack *init();
void push(stack *token_stack, token value);
token pop(stack *token_stack);
void destroy(stack *token_stack);

#endif