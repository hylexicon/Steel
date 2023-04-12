%{
#include <stdbool.h>
%}

%union {
    bool boolean;

    char c;
    char* str;

    short s;
    int integer;
    long l;
    long long ll;

    float f;
    double d;
}

%token EOL

%token<boolean> LIT_BOOL

%token<s>   LIT_SH
%token<integer> LIT_INT
%token<l>   LIT_LONG
%token<ll>  LIT_LLONG

%token<c> LIT_CH
%token<str> LIT_STR

%token<f>   LIT_FL
%token<d>   LIT_D

%token  PLUS DASH STAR SLASH PCT DLTDGT
%token  PEQ MEQ STEQ SLEQ PCTEQ DLTEQ DGTEQ
%token  AMP BAR CARET TILDE
%token  AMPEQ BAREQ CAREQ TILEQ
%token  LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE
%token  SEMI COMMA DOT COLON
%token  ELLIP
%token  EQ
%token  EXCL
%token  LT GT DEQ NEQ
%token  LTE GTE
%token  TAB NL
%token  CLASS FUN RET
%token  WHILE FOR IF ELSE
%token  IS IN
%token  MUT CONST
%token  STR NUM BOOL

%%

%%
