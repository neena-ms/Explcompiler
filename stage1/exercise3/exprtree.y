%{
    #include<stdlib.h>
    #include<stdio.h>
    #include "exprtree.h"
    #include "exprtree.c"
    int yylex(void);
%}

%union
{
    struct tnode *no;
}
%type <no> expr NUM program END
%token NUM PLUS MINUS MUL DIV END
%left PLUS MINUS
%left MUL DIV

%%
program : expr END {
                    $$=$2;
                    printf("Answer: %d\n",evaluate($1));
                    printf("The prefix notation is ");
                    prefix($1);
                    printf("\nThe postfix notation is ");
                    postfix($1);
                    printf("\n");
                    FILE *fptr=fopen("assembly.xsm","w");
                    fprintf(fptr,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\nBRKP\n",0,2056,0,0,0,0,0,0);
                    assembly($1,fptr);
                    result(fptr);
                    exit(1);
                    }
        ;
expr : PLUS expr expr {$$=makeOperatorNode('+',$2,$3);}
     | MINUS expr expr {$$=makeOperatorNode('-',$2,$3);}
     | MUL expr expr {$$=makeOperatorNode('*',$2,$3);}
     | DIV expr expr {$$=makeOperatorNode('/',$2,$3);}
     | '(' expr ')' {$$=$2;}
     | NUM       {$$=$1;}    
     ;
%%
yyerror(char const *s)
{
    printf("yyerror %s",s);
}

int main(void)
{
    yyparse();
    return 0;
}
