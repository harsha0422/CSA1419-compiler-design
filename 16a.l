%{
#include<stdio.h>
int v=0;
int c=0;
%}
%%
[ \t\n]+;
[aeiouAEIOU] {v++;}
[^aeiouAEIOU] {c++;}
%%
int main( )
{
printf ("Enter the input String :\n");
yylex();
printf("no of vowels are %d\n",v);
printf("No of consonants are %d \n",c);
}
int yywrap( )
{
return 1;
}
