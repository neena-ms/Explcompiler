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
        return 0;
    }

    else if (t->nodetype==4)
    {
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
            if (*(t->varname)=='+')
            {
                 return p+q;
            }
            if (*(t->varname)=='-')
            {
                 return p-q;
            }
            if (*(t->varname)=='*')
            {
                 return p*q;
            }
            if (*(t->varname)=='/')
            {
                 return p/q;
            }
        }
    }
return 0;
}
