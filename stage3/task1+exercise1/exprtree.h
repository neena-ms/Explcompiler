#define inttype 1
#define booltype 0
typedef struct tnode
{
    int val;
    int type; //int=1,bool=0
    char* varname;
    int nodetype; // leaf=0,read=1,write=2,connector=3,operator=4,while=5,if=6
    struct tnode *left,*mid,*right;
}tnode;

struct tnode* makeLeafNodenum(int n);
struct tnode* createTree(int val,int type, char *c,int nodetype,struct tnode *l,struct tnode *m,struct tnode *r);
struct tnode* makeLeafNodevar(char c);
int evaluate(struct tnode *t);
