%{
#include <float.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "parser.tab.h"
%}
short   -*[0-9]{1,4}
integer -*[0-9]{5,9}
long    -*[0-9]{10,18}
llong   -*[0-9]{19,}
float   -*[0-9]{1,36}[.][0-9]{1,36}
double  -*[0-9]{1,306}[.][0-9]{1,306}
char    \"([^'\\\n]|\\.)\"
string  \"(\\.|[^"\\])*\"
bool    true|false
id  [A-Za-z][A-Za-z0-9]*

%%
{short}   {
    yylval.s = atos(yytext);

    return LIT_SH
}

{integer}   {
    yylval.integer = atoi(yytext);

    return LIT_INT
}

{long}   {
    yylval.l = atol(yytext);

    return LIT_LONG
}

{llong}   {
    yylval.ll = atoll(yytext);

    return LIT_LLONG
}

{float} {
    yylval.f = strtof(yytext, NULL);

    return LIT_FL;
}

{double} {
    yylval.d = atof(yytext);

    return LIT_D;
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

    return LIT_BOOL;
}

"+" { return PLUS; }
"-" { return DASH; }
"*" { return STAR; }
"/" { return SLASH; }
"%" { return PCT; }
"<<"    { return DLT; }
">>"    { return DGT; }

"+=" { return PEQ; }
"-=" { return MEQ; }
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

yywrap() {}
