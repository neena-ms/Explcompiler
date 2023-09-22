%{
    #include<stdlib.h>
    #include<stdio.h>
    #include "exprtree.h"
    #include "exprtree.c"
    int yylex();
    int yyerror();
%}

%union
{
    struct tnode *no;
}
%type <no> expr NUM program ID BEGINNEW END Slist stmt input output asgn 
%token NUM PLUS MINUS MUL DIV EQUAL ID BEGINNEW END READ WRITE
%left EQUAL
%left PLUS MINUS
%left MUL DIV

%%
program : BEGINNEW Slist END {
                    $$=$2;
                    FILE *fptr=fopen("assembly.xsm","w");
                    fprintf(fptr,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\nBRKP\n",0,2056,0,0,0,0,0,0);
                    int p=codeGen($2,fptr);
                    fprintf(fptr,"RET\n");
                    exit(1);
                    }
        | BEGINNEW END {exit(1);}
        ;

expr : expr PLUS expr {$$=createTree(0,4,'+',$1,$3);}
     | expr MINUS expr {$$=createTree(0,4,'-',$1,$3);}
     | expr MUL expr {$$=createTree(0,4,'*',$1,$3);}
     | expr DIV expr {$$=createTree(0,4,'/',$1,$3);}
     | '(' expr ')' {$$=$2;}
     | NUM       {$$=$1;}    
     | ID        {$$=$1;}
     ;

Slist : Slist stmt {$$=createTree(0,3,' ',$1,$2);}
      | stmt
      ;

stmt : input | output | asgn;

input : READ '(' expr ')' {$$=createTree(0,1,'r',$3,NULL);};

output : WRITE '(' expr ')' {$$=createTree(0,2,'w',$3,$3);};

asgn : expr EQUAL expr  {$$=createTree(0,4,'=',$1,$3);}
     ;

%%
yyerror(char const *s)
{
    printf("yyerror %s",s);
}

int main()
{
    extern FILE *yyin;
    yyin=fopen("inputfile.txt","r");
    yyparse();
    return 0;
}
