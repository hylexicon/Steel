#pragma once
#include "token.h"

#include <stdbool.h>

typedef struct LEXER_STRUCT {
    char current;
    unsigned int index;
    char* contents;
} lexer_T;

lexer_T* init_lexer(char* contents);

void lexer_advance(lexer_T* lexer);

void lexer_skip_whitespace(lexer_T* lexer);

token_T* lexer_get_next_token(lexer_T* lexer);

token_T* lexer_collect_string(lexer_T* lexer);

token_T* lexer_collect_id(lexer_T* lexer);

token_T* lexer_collect_operator(lexer_T* lexer, int type, char* operator);

token_T* lexer_collect_single_char(lexer_T* lexer, int type);

token_T* lexer_advance_with_token(lexer_T* lexer, token_T* token);

char* lexer_get_current_char_as_string(lexer_T* lexer);

bool lexer_strncmp(lexer_T* lexer, char* str);
