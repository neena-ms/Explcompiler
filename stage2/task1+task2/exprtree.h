typedef struct tnode
{
    int val;
    int type;
    char* varname;
    int nodetype; // leaf=0,read=1,write=2,connector=3,operator=4
    struct tnode *left,*right;
}tnode;

struct tnode* makeLeafNodenum(int n);
struct tnode* createTree(int val,int type, char *c,struct tnode *l,struct tnode *r);
struct tnode* makeLeafNodevar(char c);
int getReg();
int freeReg();
int codeGen(struct tnode *t,FILE *fptr);
