%{
#include <stdio.h>
%}

%option noyywrap

%%

[a-zA-Z][a-zA-Z0-9_]* {
    printf("Valid variable: %s\n", yytext);
}

. {
    printf("Invalid variable: %s\n", yytext);
    return 0;
}

%%

int main() {
    yylex();
    return 0;
}

