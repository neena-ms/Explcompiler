struct tnode* makeLeafNodenum(int n)
{
    struct tnode* temp;
    temp=(struct tnode*)malloc(sizeof(struct tnode));
    temp->type=0;
    temp->val=n;
    temp->varname=NULL;
    temp->nodetype=0;
    temp->left=NULL;
    temp->mid=NULL;
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
    temp->mid=NULL;
    temp->right=NULL;
    return temp;
}

struct tnode* createTree(int val,int type,char *c,int nodetype,struct tnode *l,struct tnode *m,struct tnode *r)
{
    struct tnode* temp;
    temp=(struct tnode*)malloc(sizeof(struct tnode));
    temp->type=type;
    temp->val=0;
    temp->varname=malloc(sizeof(char));
    temp->varname=c;
    temp->nodetype=nodetype;
    temp->left=l;
    temp->mid=m;
    temp->right=r;
    if (nodetype==4 && type==inttype && (l->type==booltype || r->type==booltype))
    { printf("Type mismatch\n");
      exit(1);
    }
    if ((nodetype==5 || nodetype==6 || nodetype==8 || nodetype==9) && l->type==inttype)
    { printf("Type mismatch\n");
      exit(1);
    }
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
int label=-1;
int getLabel()
{
    label++;
    return label;
}
int codeGen(struct tnode *t,FILE *fptr)
{
    int p,q,r,s,loc;
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
         q=codeGen(t->left,fptr);
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
         freeReg();
         return 0;
    }

    else if (t->nodetype==3)
    {
        p=codeGen(t->left,fptr);
        q=codeGen(t->right,fptr);
        if (p!=0 || q!=0)
        { printf("Error\n");
          exit(1);
        }
        return 0;
    }

    else if (t->nodetype==4)
    {
        if (t->type==booltype)
        {
            p=codeGen(t->left,fptr);
            q=codeGen(t->right,fptr);
            if (!(strcmp(t->varname,">=")))
                {fprintf(fptr,"GE R%d,R%d\n",p,q);}
            else if (!(strcmp(t->varname,">")))
                {fprintf(fptr,"GT R%d,R%d\n",p,q);}
            else if (!(strcmp(t->varname,"<=")))
                {fprintf(fptr,"LE R%d,R%d\n",p,q);}
            else if (!(strcmp(t->varname,"<")))
                {fprintf(fptr,"LT R%d,R%d\n",p,q);}
            else if (!(strcmp(t->varname,"==")))
                {fprintf(fptr,"EQ R%d,R%d\n",p,q);}
            else if (!(strcmp(t->varname,"!=")))
                {fprintf(fptr,"NE R%d,R%d\n",p,q);}
            freeReg();
            return p;
        }
        if (*(t->varname)=='=')
        {
            p=codeGen(t->right,fptr);
            loc=4096+(*(t->left->varname)-'a');
            fprintf(fptr,"MOV [%d],R%d\n",loc,max);
            freeReg();
            return 0;
        }
        else
        {
            p=codeGen(t->left,fptr);
            q=codeGen(t->right,fptr);
            if (!(strcmp(t->varname,"+")))
            {
                 fprintf(fptr,"ADD R%d,R%d\n",p,q);
            }
            if (!(strcmp(t->varname,"-")))
            {
                 fprintf(fptr,"SUB R%d,R%d\n",p,q);
            }
            if (!(strcmp(t->varname,"*")))
            {
                 fprintf(fptr,"MUL R%d,R%d\n",p,q);
            }
            if (!(strcmp(t->varname,"/")))
            {
                 fprintf(fptr,"DIV R%d,R%d\n",p,q);
            }
            freeReg();
            return p;
        }
    }

    else if (t->nodetype==5)
       {
        s=getLabel();
        fprintf(fptr,"L%d:\n",s);
        p=codeGen(t->left,fptr);
        r=getLabel();
        fprintf(fptr,"JZ R%d,L%d\n",p,r);
        freeReg();
        p=codeGen(t->right,fptr);
        fprintf(fptr,"JMP L%d\n",s);
        fprintf(fptr,"L%d:\n",r);
        return p;
    }


    else if (t->nodetype==6)
    {
         p=codeGen(t->left,fptr);
         s=getLabel();
         fprintf(fptr,"JZ R%d,L%d\n",p,s);
         freeReg();
         p=codeGen(t->mid,fptr);
         if (!(strcmp(t->varname,"ifelse")))
         {
         r=getLabel();
         fprintf(fptr,"JMP L%d\n",r);
         fprintf(fptr,"L%d:\n",s);
         p=codeGen(t->right,fptr);
         fprintf(fptr,"L%d:\n",r);
         }
         else if (!(strcmp(t->varname,"if")))
         {fprintf(fptr,"L%d:\n",s);}
         return p;
    }
return 0;
}