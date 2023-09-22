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

int A[26];

int evaluate(struct tnode *t)
{
    int p,q,loc;
    if (t->nodetype==0)
    {
        if (t->varname==NULL)
        {
             return t->val;
        }
        else
        {
            loc=*(t->varname)-'a';
            return A[loc];
        }
    }

    else if(t->nodetype==1)
    {
        loc=*(t->left->varname)-'a';
        scanf("%d",&A[loc]);
        return 0;
    }

    else if (t->nodetype==2)
    {
         q=evaluate(t->left);
         printf("%d\n",q);
         return 0;
    }

    else if (t->nodetype==3)
    {
        p=evaluate(t->left);
        q=evaluate(t->right);
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
            p=evaluate(t->left);
            q=evaluate(t->right);
            if (!(strcmp(t->varname,">=")))
                {if (p>=q)
                 {return 1;}
                 else
                 {return 0;}
                 }
            else if (!(strcmp(t->varname,">")))
                 {if (p>q){return 1;} else {return 0;}}
            else if (!(strcmp(t->varname,"<=")))
                 {if (p<=q){return 1;} else {return 0;}}
            else if (!(strcmp(t->varname,"<")))
                 {if (p<q){return 1;} else {return 0;}}
            else if (!(strcmp(t->varname,"==")))
                 {if (p==q){return 1;} else {return 0;}}
            else if (!(strcmp(t->varname,"!=")))
                 {if (p!=q){return 1;} else {return 0;}}
           return 0;
        }
        if (*(t->varname)=='=')
        {
            p=evaluate(t->right);
            loc=*(t->left->varname)-'a';
            A[loc]=p;
            return 0;
        }
        else
        {
            p=evaluate(t->left);
            q=evaluate(t->right);
            if (!strcmp(t->varname,"+"))
            {
                 return p+q;
            }
            if (!strcmp(t->varname,"+"))
            {
                 return p-q;
            }
            if (!strcmp(t->varname,"*"))
            {
                 return p*q;
            }
            if (!strcmp(t->varname,"/"))
            {
                 return p/q;
            }
        }
       }

    else if (t->nodetype==5)
   {
    p=evaluate(t->left);
    while (p==1)
    {p=evaluate(t->right);
     p=evaluate(t->left);
    }
    return 0;
    }

    else if (t->nodetype==6)
    {
         p=evaluate(t->left);
         if (p==1)
         {p=evaluate(t->mid);}
         else
         {p=evaluate (t->right);}
         return 0;
    }

return 0;
}
