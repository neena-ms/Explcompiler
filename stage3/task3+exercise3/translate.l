%{
    #include<stdio.h>
    #include<stdlib.h>
    #include "translate.c"
    int add=2040,first=0,label=0;
    FILE *ptr;

%}
NUM [0-9]
%%
("L"[0-9]+[:])  {label=1;
                    char *labelname=malloc(yyleng*sizeof(char));
                    strcpy(labelname,yytext);
                    if (first==0)
                    {
                    label=1;
                    append_table(labelname,add);
                    add-=2;
                    }
                    };

"JZ R"[0-9]+[,]"L"[0-9]+  {if (first!=0)
                        {
                            if (yytext[5]==',')
                            {
                            fprintf(ptr,"JZ R%c,",yytext[4]);
                            fprintf(ptr,"%d",findadd(yytext+6));
                            }
                            else 
                            {
                                fprintf(ptr,"JZ R%c%c,",yytext[4],yytext[5]);
                                fprintf(ptr,"%d",findadd(yytext+7));
                            }
                        }
                        }

"JNZ R"[0-9]+[,]"L"[0-9]+ {if (first!=0) 
                           {
                            if (yytext[6]==',')
                            {
                            fprintf(ptr,"JNZ R%c,",yytext[5]);
                            fprintf(ptr,"%d",findadd(yytext+7));
                            }
                            else
                            {
                                fprintf(ptr,"JNZ R%c%c,",yytext[5],yytext[6]);
                                fprintf(ptr,"%d",findadd(yytext+8));
                            }
                        }
                        }

"JMP L"[0-9]+ { if (first!=0)
              {
                    fprintf(ptr,"JMP %d",findadd(yytext+4));
                }
                }

"\n" {    add+=2;
          if (first!=0) 
          { 
          if (label==0)
          {fprintf(ptr,"\n");}
          else 
          {label--;} }
     };
. {if (first!=0) {fprintf(ptr,"%s",yytext);}};

%%
int yywrap()
{
    if (first==0)
    {
        yyin=fopen("assembly.xsm","r");
        first=1;
        return 0;
    }
    if (first!=0)
    {
    return 1;
    }
}
int main()
{
ptr=fopen("assembly2.xsm","w");
extern FILE* yyin;
yyin=fopen("assembly.xsm","r");
yylex();
return 0;
}
