struct tnode* makeLeafNode(int n)
{
    struct tnode* temp;
    temp=(struct tnode*)malloc(sizeof(struct tnode));
    temp->op=NULL;
    temp->val=n;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}

struct tnode* makeOperatorNode(char c,struct tnode *l,struct tnode *r)
{
    struct tnode* temp;
    temp=(struct tnode*)malloc(sizeof(struct tnode));
    temp->op=malloc(sizeof(char));
    *(temp->op)=c;
    temp->left=l;
    temp->right=r;
    return temp;
}

int evaluate(struct tnode *t)
{
    if (t->op==NULL)
    {
        return t->val;
    }
    else
    {
        switch(*(t->op))
        {
            case '+' : return evaluate(t->left)+evaluate(t->right);
		       break;
	    case '-' : return evaluate(t->left)-evaluate(t->right);
                       break;
            case '*' : return evaluate(t->left)*evaluate(t->right);
                       break;
            case '/' : return evaluate(t->left)/evaluate(t->right);
                       break;
        }
    }
}

void prefix(struct tnode *t)
{
    if (t->op==NULL)
    {
        printf("%d ",t->val);
        return;
    }
    printf("%c ",*(t->op));
    prefix(t->left);
    prefix(t->right);
}

void postfix(struct tnode *t)
{
    if (t->op==NULL)
    {
        printf("%d ",t->val);
        return;
    }
    postfix(t->left);
    postfix(t->right);
    printf("%c ",*(t->op));
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
    if (max<=0)
    {
        printf("All registers are free");
        return 0;
    }
    max-=1;
    return max;
}
void assembly(struct tnode *t,FILE *fptr)
{
    if (t->op==NULL)
    {
        int p=getReg();
        fprintf(fptr,"MOV R%d,%d\n",p,t->val);
        return;
    }
    assembly(t->left,fptr);
    assembly(t->right,fptr);
    switch (*(t->op))
    {
         case '+' : fprintf(fptr,"ADD R%d,R%d\n",max-1,max);
                    break;
         case '-' : fprintf(fptr,"SUB R%d,R%d\n",max-1,max);
                    break;
         case '*' : fprintf(fptr,"MUL R%d,R%d\n",max-1,max);
                    break;
         case '/' : fprintf(fptr,"DIV R%d,R%d\n",max-1,max);
                    break;
    }
    freeReg();
    return;
}

void result(FILE *fptr)
{
    fprintf(fptr,"MOV SP,4095\nPUSH R0\nMOV R1,\"Write\"\nPUSH R1\nMOV R1,-2\nPUSH R1\nPUSH R0\nPUSH R1\nPUSH R1\nCALL 0\nPOP R1\nPOP R1\nPOP R1\nPOP R1\nPOP R1\nRET\n");
}
