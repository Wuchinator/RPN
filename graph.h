#ifndef DRAW_GRAPH
#define DRAW_GRAPH
#include <math.h>
#include <stdio.h>

#include "rpn_head.h"
#include "stack.h"

#define leftside 0
#define rightside (4 * M_PI)
#define bellow -1
#define up 1

#define WIDTH 80
#define HEIGHT 25

void dots_count(int **matrix, token *rpn_tokens, int rpn_tokens_size);

void create_matrix(int *arr, int **matrix);

void draw(int **matrix);

#endif