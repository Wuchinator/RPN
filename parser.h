#ifndef PARSER_TOKENS
#define PARSER_TOKENS
#include <stdlib.h>
#include <string.h>

#include "stack.h"

token *parse(char *function, int *flag, int *tokens_size_ptr);

token uno_opers(char **function, int *flag);

token bin_opers(const char *function, int *flag);

token *token_extending(token *tokens, int *tokens_max_size, int *flag);

token getter_number(char **function, int *flag);

#endif