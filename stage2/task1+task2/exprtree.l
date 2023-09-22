%{
    #include<stdlib.h>
    #include<stdio.h>
    #include "y.tab.h"
    #include "exprtree.h"
    int number;
%}
%%
"begin" {return BEGINNEW;}
"end" {return END;}
"read" {return READ;}
"write" {return WRITE;}
[0-9]+ {number=atoi(yytext);yylval.no=makeLeafNodenum(number); return NUM;}
[a-z] {yylval.no=makeLeafNodevar(*yytext);return ID;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
"=" {return EQUAL;}
";" {}
" " {}
[ \t] {}
[()] {return *yytext;}
[\n] {}
.    {yyerror("unknown character\n");exit(1);}
%%
int yywrap(void)
{
    return 1;
}
