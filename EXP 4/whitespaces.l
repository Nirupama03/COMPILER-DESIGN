%{
    #include<stdio.h>
%}

%option noyywrap

%%
"/*"([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+"/" 
"//"(.*)[\r\n]   
[ \t]+
.       { printf("%s", yytext); }
%%

int main()
{
    FILE *file = fopen("expression.txt", "r");

    if (!file) {
        fprintf(stderr, "Failed to open input file.\n");
        return 1;
    }
    yyin = file;
    yylex();
    fclose(file);
    printf("\n");
    return 0;
}

