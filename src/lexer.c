#include "include/lexer.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

lexer_T* init_lexer(char* contents) {
    lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));

    lexer->contents = contents;
    lexer->index = 0;
    lexer->current = contents[lexer->index];

    return lexer;
}

void lexer_advance(lexer_T* lexer) {
    if (lexer->current != '\0' && lexer->index < strlen(lexer->contents)) {
        lexer->index += 1;
        lexer->current = lexer->contents[lexer->index];
    }
}

void lexer_skip_whitespace(lexer_T* lexer) {
    while (lexer->current == ' ')
        lexer_advance(lexer);
}

token_T* lexer_get_next_token(lexer_T* lexer) {
    while (lexer->current != '\0' && lexer->index < strlen(lexer->contents)) {
        if (lexer_strncmp(lexer, "    "))
            return lexer_collect_operator(lexer, TOKEN_INDENT, "    ");

        else if (lexer->current == ' ')
            lexer_skip_whitespace(lexer);

        else if (isalnum(lexer->current))
            return lexer_collect_id(lexer);

        else if (lexer->current == '"')
            return lexer_collect_string(lexer);

        else if (lexer_strncmp(lexer, "!=="))
            return lexer_collect_operator(lexer, TOKEN_NOT_DOUBLE_EQUAL, "!==");
        
        else if (lexer_strncmp(lexer, "!="))
            return lexer_collect_operator(lexer, TOKEN_NOT_EQUAL, "!=");
        
        else if (lexer_strncmp(lexer, "<="))
            return lexer_collect_operator(lexer, TOKEN_LESS_EQUAL, "<=");

        else if (lexer_strncmp(lexer, ">="))
            return lexer_collect_operator(lexer, TOKEN_GREATER_EQUAL, ">=");

        else if (lexer_strncmp(lexer, "==="))
            return lexer_collect_operator(lexer, TOKEN_TRIPLE_EQUALS, "===");

        else if (lexer_strncmp(lexer, "=="))
            return lexer_collect_operator(lexer, TOKEN_DOUBLE_EQUALS, "==");

        else if (lexer_strncmp(lexer, "+="))
            return lexer_collect_operator(lexer, TOKEN_PLUS_EQUALS, "+=");

        else if (lexer_strncmp(lexer, "-="))
            return lexer_collect_operator(lexer, TOKEN_DASH_EQUALS, "-=");

        else if (lexer_strncmp(lexer, "*="))
            return lexer_collect_operator(lexer, TOKEN_STAR_EQUALS, "*=");

        else if (lexer_strncmp(lexer, "//="))
            return lexer_collect_operator(lexer, TOKEN_DOUBLE_SLASH_EQUALS, "//=");

        else if (lexer_strncmp(lexer, "//"))
            return lexer_collect_operator(lexer, TOKEN_DOUBLE_SLASH, "//");

        else if (lexer_strncmp(lexer, "/="))
            return lexer_collect_operator(lexer, TOKEN_DASH_EQUALS, "/=");

        else if (lexer_strncmp(lexer, "&="))
            return lexer_collect_operator(lexer, TOKEN_AMPER_EQUALS, "&=");

        else if (lexer_strncmp(lexer, "|="))
            return lexer_collect_operator(lexer, TOKEN_BAR_EQUALS, "|=");

        else if (lexer_strncmp(lexer, "^="))
            return lexer_collect_operator(lexer, TOKEN_CARET_EQUALS, "^=");

        else if (lexer_strncmp(lexer, "..."))
            return lexer_collect_operator(lexer, TOKEN_NOT_EQUAL, "...");

        else if (lexer_strncmp(lexer, "??"))
            return lexer_collect_operator(lexer, TOKEN_DOUBLE_QUESTION, "??");
        
        switch (lexer->current) {
            case '+':
                return lexer_collect_single_char(lexer, TOKEN_PLUS);
            
            case '-':
                return lexer_collect_single_char(lexer, TOKEN_DASH);

            case '*':
                return lexer_collect_single_char(lexer, TOKEN_STAR);

            case '/':
                return lexer_collect_single_char(lexer, TOKEN_SLASH);

            case '%':
                return lexer_collect_single_char(lexer, TOKEN_PERCENT);

            case '^':
                return lexer_collect_single_char(lexer, TOKEN_CARET);

            case '=':
                return lexer_collect_single_char(lexer, TOKEN_EQUALS);
            
            case ';':
                return lexer_collect_single_char(lexer, TOKEN_SEMI);

            case ':':
                return lexer_collect_single_char(lexer, TOKEN_COLON);
            
            case '(':
                return lexer_collect_single_char(lexer, TOKEN_LPAREN);

            case ')':
                return lexer_collect_single_char(lexer, TOKEN_RPAREN);

            case '[':
                return lexer_collect_single_char(lexer, TOKEN_LBRACKET);

            case ']':
                return lexer_collect_single_char(lexer, TOKEN_RBRACKET);
            
            case '{':
                return lexer_collect_single_char(lexer, TOKEN_LBRACE);

            case '}':
                return lexer_collect_single_char(lexer, TOKEN_RBRACE);

            case '\n':
                return lexer_collect_single_char(lexer, TOKEN_NEWLINE);

            case '\t':
                return lexer_collect_single_char(lexer, TOKEN_INDENT);

            case '<':
                return lexer_collect_single_char(lexer, TOKEN_LESS);

            case '>':
                return lexer_collect_single_char(lexer, TOKEN_GREATER);

            case '&':
                return lexer_collect_single_char(lexer, TOKEN_AMPERSAND);

            case '|':
                return lexer_collect_single_char(lexer, TOKEN_BAR);

            case '.':
                return lexer_collect_single_char(lexer, TOKEN_DOT);

            case ',':
                return lexer_collect_single_char(lexer, TOKEN_COMMA);

            case '~':
                return lexer_collect_single_char(lexer, TOKEN_TILDE);

            case '?':
                return lexer_collect_single_char(lexer, TOKEN_QUESTION);
        }
    }

    return init_token(TOKEN_EOF, "\0");
}

token_T* lexer_collect_string(lexer_T* lexer) {
    lexer_advance(lexer);

    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (lexer->current != '"') {
        char* string = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(string) + 1) * sizeof(char));
        
        strcat(value, string);
        lexer_advance(lexer);
    }

    lexer_advance(lexer);

    return init_token(TOKEN_STRING, value);
}

token_T* lexer_collect_id(lexer_T* lexer) {
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (isalnum(lexer->current)) {
        char* string = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(string) + 1) * sizeof(char));

        strcat(value, string);
        lexer_advance(lexer);
    }

    return init_token(TOKEN_ID, value);
}

token_T* lexer_collect_operator(lexer_T* lexer, int type, char* operator) {
    int operatorLength = strlen(operator);

    while (operatorLength > 0) {
        lexer_advance(lexer);
        operatorLength--;
    }

    return init_token(type, operator);
}

token_T* lexer_collect_single_char(lexer_T* lexer, int type) {
    return lexer_advance_with_token(lexer, init_token(type, lexer_get_current_char_as_string(lexer)));
}

token_T* lexer_advance_with_token(lexer_T* lexer, token_T* token) {
    lexer_advance(lexer);

    return token;
}

char* lexer_get_current_char_as_string(lexer_T* lexer) {
    char* string = calloc(2, sizeof(char));
    string[0] = lexer->current;
    string[1] = '\0';

    return string;
}

bool lexer_strncmp(lexer_T* lexer, char* str) {
    return !strncmp(lexer->contents + lexer->index, str, strlen(str));
}
