%{
#include <stdio.h>
%}
DIGIT [0-9]
LETTER [a-zA-Z]
ID {LETTER}({LETTER}|{DIGIT})*
INT {DIGIT}+
OP '+'|'-'|'*'|'/'|'='
PUNCT '('|')'|'{'|'}'|';'
%%
[ \t\n]+ ;
{ID} { printf("ID: %s\n", yytext); }
{INT} { printf("INT: %s\n", yytext); }
{OP} { printf("OP: %s\n", yytext); }
{PUNCT} { printf("PUNCT: %s\n", yytext); }
{ printf("ERROR: unrecognized token '%s'\n", yytext); }
%%
int main(int argc, char** argv)
{
 yylex();
 return 0;
}
