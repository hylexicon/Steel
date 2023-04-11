%{
#include <float.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "parser.tab.h"
%}

integer [0-9]+
float   [0-9]+[.][0-9]+
char    \"([^'\\\n]|\\.)\"
string  \"(\\.|[^"\\])*\"
bool    true|false
id  [A-Za-z][A-Za-z0-9]*

%%
{integer}   {
    long value = atoll(yytext);

    if (value > SHRT_MIN && value < SHRT_MAX)
        yylval.s = (short) yytext;
    
    else if (value > INT_MIN && value < INT_MAX)
        yylval.integer = (int)yytext);
    
    else if (value > LONG_MIN && value < LONG_MAX)
        yylval.l = (long) value;
    
    else if (value < LONG_MIN && value > LONG_MAX)
        yylval.ll = value;
    
    return LIT_INT;
}

{float} {
    double value = atof(yytext);

    if (value > FLT_MIN && value < FLT_MAX)
        yyval.f = (float) value;
    
    else
        yyval.d = value;

    return LIT_FL;
}

{char}  {
    yylval.character = yytext[1];

    return LIT_CH;
}

{string}    {
    assert(str != 0);
    size_t len = strlen(str);
    memmove(str, str+1, len);
    str[strlen(str) - 1] = 0;
    
    yylval.string = strdup(yytext);
    
    return LIT_STR;
}

{bool}  {
    yylval.boolean = strcmp(yytext, "true") == 0

    return TOK_BOOL_LIT;
}

"+" { return PLUS; }
"-" { return DASH; }
"*" { return STAR; }
"/" { return SLASH; }
"%" { return PCT; }
"<<"    { return DLT; }
">>"    { return DGT; }

"+=" { return PEQ; }
"-=" { return DEQ; }
"*=" { return STEQ; }
"/=" { return SLEQ; }
"%=" { return PCTEQ; }
"<<="    { return DLTEQ; }
">>="    { return DGTEQ; }

"&" { return AMP; }
"|" { return BAR; }
"^" { return CARET; }
"~" { return TILDE; }

"&="    { return AMPEQ; }
"|="    { return BAREQ; }
"^="    { return CAREQ; }
"~="    { return TILEQ; }

"(" { return LPAREN; }
")" { return RPAREN; }
"[" { return LBRACKET; }
"]" { return RBRACKET; }
"{" { return LBRACE; }
"}" { return RBRACE; }

";" { return SEMI; }
"," { return COMMA; }
"." { return DOT; }
":" { return COLON; }

"..."   { return ELLIP; }

"=" { return EQ; }

"!" { return EXCL; }

"<" { return LT; }
">" { return GT; }
"=="    { return DEQ; }
"!="    { return NEQ; }

"<="    { return LTE; }
">="    { return GTE; }

[(    )|\t] { return TAB; }
"\n"    { return NL; }

"class" { return CLASS; }
"fun"   { return FUN; }
"return"    { return RET; }

"while" { return WHILE; }
"for" { return FOR; }
"if" { return IF; }
"else"  { return ELSE; }

"is":   { return IS; }
"in":   { return IN; }

"mut"   { return MUT; }
"const"   { return CONST; }

"str"   { return STR; }
"num"   { return NUM; }
"bool"  { return BOOL; }

--[^-]*(\n|$)
---(.|\n)*---
[\n\r]
%%

