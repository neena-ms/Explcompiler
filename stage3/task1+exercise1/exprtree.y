%{
    #include<stdlib.h>
    #include<stdio.h>
    #include<string.h>
    #include "exprtree.h"
    #include "exprtree.c"
    int yylex();
    void yyerror();
%}

%union
{
    struct tnode *no;
}
%type <no> expr NUM program ID BEGINNEW END Slist stmt input output asgn ifstmt whilestmt
%token NUM PLUS MINUS MUL DIV EQUAL ID BEGINNEW END READ WRITE IF WHILE DO END ENDIF ENDWHILE ELSE THEN LE GE LT GT NE EQEQ
%left EQUAL LE GE LT GT EQEQ NE
%left PLUS MINUS
%left MUL DIV

%%
program : BEGINNEW Slist END {
                    $$=$2;
                    int p=evaluate($2);
                    exit(1);
                    }
        | BEGINNEW END {exit(1);}
        ;

Slist : Slist stmt {$$=createTree(0,0,"connector",3,$1,NULL,$2);}
      | stmt  {$$=$1;}
      ;

stmt : input {$$=$1;} | output {$$=$1;} | asgn {$$=$1;} | ifstmt {$$=$1;} | whilestmt {$$=$1;} | BREAK {$$=$1;} | CONTINUE {$$=$1;};
input : READ '(' expr ')' {$$=createTree(0,1,"read",1,$3,NULL,NULL);};

output : WRITE '(' expr ')' {$$=createTree(0,1,"write",2,$3,NULL,$3);};

asgn : expr EQUAL expr  {$$=createTree(0,1,"=",4,$1,NULL,$3);}
     ;

ifstmt : IF '(' expr ')' THEN Slist ELSE Slist ENDIF {$$=createTree(0,1,"ifelse",6,$3,$6,$8);}
       | IF '(' expr ')' THEN Slist ENDIF {$$=createTree(0,1,"if",6,$3,$6,NULL);}
       ;

whilestmt : WHILE '(' expr ')' DO Slist ENDWHILE {$$=createTree(0,1,"while",5,$3,NULL,$6);};

expr : expr PLUS expr {$$=createTree(0,1,"+",4,$1,NULL,$3);}
     | expr MINUS expr {$$=createTree(0,1,"-",4,$1,NULL,$3);}
     | expr MUL expr {$$=createTree(0,1,"*",4,$1,NULL,$3);}
     | expr DIV expr {$$=createTree(0,1,"/",4,$1,NULL,$3);}
     | expr LE expr {$$=createTree(0,0,"<=",4,$1,NULL,$3);}
     | expr LT expr {$$=createTree(0,0,"<",4,$1,NULL,$3);}
     | expr GE expr {$$=createTree(0,0,">=",4,$1,NULL,$3);}
     | expr GT expr {$$=createTree(0,0,">",4,$1,NULL,$3);}
     | expr EQEQ expr {$$=createTree(0,0,"==",4,$1,NULL,$3);}
     | expr NE expr {$$=createTree(0,0,"!=",4,$1,NULL,$3);}
     | '(' expr ')' {$$=$2;}
     | NUM       {$$=$1;}    
     | ID        {$$=$1;}
     ;

%%
yyerror(char const *s)
{
    printf("yyerror %s",s);
}

int main()
{
    extern FILE *yyin;
    yyin=fopen("inputfile2.txt","r");
    yyparse();
    return 0;
}
