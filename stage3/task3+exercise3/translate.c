struct LTable
{
    char* labelname;
    int add;
    struct LTable *next;
}*LThead,*LTtail;

void append_table(char *labelname,int add)
{
    struct LTable *temp;
    temp=(struct LTable *)malloc(sizeof(struct LTable));
    temp->labelname=labelname;
    temp->add=add;
    if (LThead==NULL)
    {
        LThead=LTtail=temp;
    }
    else
    {
        LTtail->next=temp;
        LTtail=LTtail->next;
    }
    return;
}

int findadd(char *c)
{
    struct LTable *temp;
    temp=(struct LTable *)malloc(sizeof(struct LTable));
    temp=LThead;
    while(temp!=NULL)
    {
        if ((((temp->labelname)[0]) == (c[0])) && (((temp->labelname)[1])==(c[1])))
         {return temp->add;}
        temp=temp->next;
    }
    return -1;
}

void printtable()
{
    struct LTable *temp;
    temp=(struct LTable *)malloc(sizeof(struct LTable));
    temp=LThead;
    while(temp!=NULL)
    {
        printf("%s,%d\n",temp->labelname,temp->add);
        temp=temp->next;
    }
    return;
}
