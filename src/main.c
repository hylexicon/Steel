#include "include/lexer.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
    lexer_T* lexer = init_lexer("");

    token_T* token = NULL;

    while((token = lexer_get_next_token(lexer)) != NULL)
        printf("TOKEN(%d, %s)\n", token->type, token->value);

    return 0;
}
