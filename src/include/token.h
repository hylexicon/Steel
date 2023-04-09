#ifndef TOKEN_H
#define TOKEN_H
typedef struct TOKEN_STRUCT {
    enum {
        TOKEN_ID,
        TOKEN_EQUALS,
        TOKEN_PLUS,
        TOKEN_DASH,
        TOKEN_STAR,
        TOKEN_SLASH,
        TOKEN_CARET,
        TOKEN_PERCENT,
        TOKEN_STRING,
        TOKEN_SEMI,
        TOKEN_COLON,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_LBRACE,
        TOKEN_RBRACE,
        TOKEN_LBRACKET,
        TOKEN_RBRACKET,
        TOKEN_LESS,
        TOKEN_LESS_EQUAL,
        TOKEN_GREATER,
        TOKEN_GREATER_EQUAL,
        TOKEN_NOT_EQUAL,
        TOKEN_NOT_DOUBLE_EQUAL,
        TOKEN_DOUBLE_EQUALS,
        TOKEN_TRIPLE_EQUALS,
        TOKEN_INDENT,
        TOKEN_NEWLINE,
        TOKEN_AMPERSAND,
        TOKEN_BAR,
        TOKEN_EXCLAMATION,
        TOKEN_PLUS_EQUALS,
        TOKEN_DASH_EQUALS,
        TOKEN_STAR_EQUALS,
        TOKEN_SLASH_EQUALS,
        TOKEN_PERCENT_EQUALS,
        TOKEN_AMPER_EQUALS,
        TOKEN_BAR_EQUALS,
        TOKEN_CARET_EQUALS,
        TOKEN_DOT,
        TOKEN_ELLIPSES,
        TOKEN_DOUBLE_SLASH,
        TOKEN_DOUBLE_SLASH_EQUALS,
        TOKEN_COMMA,
        TOKEN_TILDE,
        TOKEN_QUESTION,
        TOKEN_DOUBLE_QUESTION
    } type;

    char* value;
} token_T;

token_T* init_token(int type, char* value);
#endif