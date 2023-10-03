#include "graph.h"

#include "get_func.h"
#include "parser.h"
#include "rpn_head.h"
#include "stack.h"

int main() {
    int flag = 0;
    char *function = input_func(&flag);
    int all_set_tokens_size = 0;
    token *all_set_tokens = parse(function, &flag, &all_set_tokens_size);
    int rpn_set_size = all_set_tokens_size;
    token *rpn_tokens = NULL;
    if (!flag) {
        rpn_tokens = convert_rpn(all_set_tokens, all_set_tokens_size, &rpn_set_size);
        int console_write[HEIGHT][WIDTH] = {0};
        int *matrix[HEIGHT];
        create_matrix((int *)console_write, matrix);
        dots_count(matrix, rpn_tokens, rpn_set_size);
        draw(matrix);
    } else {
        printf("n/a");
    }
    free(function);
    free(all_set_tokens);
    free(rpn_tokens);
    return 0;
}

void dots_count(int **matrix, token *rpn_tokens, int rpn_tokens_size) {
    double X_os = (double)(rightside - leftside) / (WIDTH - 1);
    double Y_os = (double)(up - bellow) / (HEIGHT - 1);
    double var_data = 0;
    for (int i = 0; i < WIDTH; i++, var_data += X_os) {
        double result = calc(rpn_tokens, rpn_tokens_size, var_data);
        if (!isnan(result) && !isinf(result)) {
            int j = round((result + 1.) / Y_os);
            if (j >= 0 && j < HEIGHT) {
                matrix[j][i] = 1;
            }
        }
    }
}

void create_matrix(int *arr, int **matrix) {
    for (int i = 0; i < HEIGHT; i++) {
        matrix[i] = arr + i * WIDTH;
    }
}

void draw(int **matrix) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (0 == matrix[i][j]) {
                printf(".");
            } else {
                printf("*");
            }
        }
        printf("\n");
    }
}