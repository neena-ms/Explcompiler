%{
    #include<stdlib.h>
    #include<stdio.h>
    #include<string.h>
    #include "y.tab.h"
    #include "exprtree.h"
    int number;
%}
%%
"begin" {return BEGINNEW;}
"end" {return END;}
"read" {return READ;}
"write" {return WRITE;}
"if" {return IF;}
"else" {return ELSE;}
"then" {return THEN;}
"endif" {return ENDIF;}
"while" {return WHILE;}
"endwhile" {return ENDWHILE;}
"do" {return DO;}
"break" {return BREAK;}
"continue" {return CONTINUE;}
[0-9]+ {number=atoi(yytext);yylval.no=makeLeafNodenum(number); return NUM;}
[a-z] {yylval.no=makeLeafNodevar(*yytext);return ID;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
"=" {return EQUAL;}
"<" {return LT;}
">" {return GT;}
"<=" {return LE;}
">=" {return GE;}
"==" {return EQEQ;}
"!=" {return NE;}
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
