struct tnode* makeLeafNodenum(int n)
{
    struct tnode* temp;
    temp=(struct tnode*)malloc(sizeof(struct tnode));
    temp->type=0;
    temp->val=n;
    temp->varname=NULL;
    temp->nodetype=0;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}

struct tnode* makeLeafNodevar(char c)
{
    struct tnode* temp;
    temp=(struct tnode*)malloc(sizeof(struct tnode));
    temp->type=0;
    temp->val=0;
    temp->varname=malloc(sizeof(char));
    *(temp->varname)=c;
    temp->nodetype=0;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}

struct tnode* createTree(int val,int type,char *c,struct tnode *l,struct tnode *r)
{
    struct tnode* temp;
    temp=(struct tnode*)malloc(sizeof(struct tnode));
    temp->type=0;
    temp->val=0;
    temp->varname=malloc(sizeof(char));
    *(temp->varname)=c;
    temp->nodetype=type;
    temp->left=l;
    temp->right=r;
    return temp;
}

int max=-1;
int getReg()
{
    if (max>=20)
    {
        printf("All registers are under use");
        return 0;
    }
    max++;
    return max;
}
int freeReg()
{
    if (max<0)
    {
        printf("All registers are free");
        return 0;
    }
    max-=1;
}
int codeGen(struct tnode *t,FILE *fptr)
{
    int p,q,loc;
    if (t->nodetype==0)
    {
        if (t->varname==NULL)
        {
             p=getReg();
             fprintf(fptr,"MOV R%d,%d\n",p,t->val);
             return p;
        }
        else
        {
            loc=4096+(*(t->varname)-'a');
            p=getReg();
            fprintf(fptr,"MOV R%d,[%d]\n",p,loc);
            return p;
        }
    }

    else if(t->nodetype==1)
    {
        fprintf(fptr,"MOV SP,%d\n",4122);
        loc=4096+(*(t->left->varname)-'a');
        p=getReg();
        fprintf(fptr,"MOV R%d,\"Read\"\n",p);
        fprintf(fptr,"PUSH R%d\n",p);
        fprintf(fptr,"MOV R%d,%d\n",p,-1);
        fprintf(fptr,"PUSH R%d\n",p);
        fprintf(fptr,"MOV R%d,%d\n",p,loc);
        fprintf(fptr,"PUSH R%d\n",p);
        fprintf(fptr,"PUSH R%d\n",p);
        fprintf(fptr,"PUSH R%d\n",p);
        fprintf(fptr,"CALL 0\n");
        fprintf(fptr,"POP R%d\n",p);
        fprintf(fptr,"POP R%d\n",p);
        fprintf(fptr,"POP R%d\n",p);
        fprintf(fptr,"POP R%d\n",p);
        fprintf(fptr,"POP R%d\n",p);
        freeReg();
        return 0;
    }

    else if (t->nodetype==2)
    {
         if (t->left->nodetype!=0)
         {
             q=codeGen(t->left,fptr);
         }
         p=getReg();
         fprintf(fptr,"MOV R%d,\"Write\"\n",p);
         fprintf(fptr,"PUSH R%d\n",p);
         fprintf(fptr,"MOV R%d,%d\n",p,-2);
         fprintf(fptr,"PUSH R%d\n",p);
         fprintf(fptr,"PUSH R%d\n",q);
         fprintf(fptr,"PUSH R%d\n",p);
         fprintf(fptr,"PUSH R%d\n",p);
         fprintf(fptr,"CALL 0\n");
         fprintf(fptr,"POP R%d\n",p);
         fprintf(fptr,"POP R%d\n",p);
         fprintf(fptr,"POP R%d\n",p);
         fprintf(fptr,"POP R%d\n",p);
         fprintf(fptr,"POP R%d\n",p);
         freeReg();
         return 0;
    }

    else if (t->nodetype==3)
    {
        p=codeGen(t->left,fptr);
        q=codeGen(t->right,fptr);
        return 0;
    }

    else if (t->nodetype==4)
    {
        if (*(t->varname)=='=')
        {
            p=codeGen(t->right,fptr);
            loc=4096+(*(t->left->varname)-'a');
            fprintf(fptr,"MOV [%d],R%d\n",loc,max);
            freeReg();
            return -1;
        }
        else
        {
            p=codeGen(t->left,fptr);
            q=codeGen(t->right,fptr);
            if (*(t->varname)=='+')
            {
                 fprintf(fptr,"ADD R%d,R%d\n",p,q);
            }
            if (*(t->varname)=='-')
            {
                 fprintf(fptr,"SUB R%d,R%d\n",p,q);
            }
            if (*(t->varname)=='*')
            {
                 fprintf(fptr,"MUL R%d,R%d\n",p,q);
            }
            if (*(t->varname)=='/')
            {
                 fprintf(fptr,"DIV R%d,R%d\n",p,q);
            }
            freeReg();
            return p;
        }
    }
return 0;
}

void result(FILE *fptr)
{
    fprintf(fptr,"MOV SP,4095\nPUSH R0\nMOV R1,\"Write\"\nPUSH R1\nMOV R1,-2\nPUSH R1\nPUSH R0\nPUSH R1\nPUSH R1\nCALL 0\nPOP R1\nPOP R1\nPOP R1\nPOP R1\nPOP R1\nRET\n");
}
