#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define LEFT 1
#define RIGHT 2

typedef struct command
{
    char verb;
    char noun;
} command;

typedef struct bst_node
{
    char key;
    struct bst_node *left, *right;
} BSTNodeT;

BSTNodeT *root;

void preorder(BSTNodeT *p, int level)
{
    int i;
    if (p != NULL)
    {
        for (i = 0; i <= level; i++)
            printf(" "); /* for nice listing */
        printf("%c\n", p->key);
        preorder(p->left, level + 1);
        preorder(p->right, level + 1);
    }
}

void inorder(BSTNodeT *p, int level)
{
    int i;
    if (p != NULL)
    {
        inorder(p->left, level + 1);
        for (i = 0; i <= level; i++)
            printf(" "); /* for nice listing */
        printf("%c\n", p->key);
        inorder(p->right, level + 1);
    }
}
void postorder(BSTNodeT *p, int level)
{
    int i;
    if (p != NULL)
    {
        postorder(p->left, level + 1);
        postorder(p->right, level + 1);
        for (i = 0; i <= level; i++)
            printf(" "); /* for nice listing */
        printf("%c\n", p->key);
    }
}

BSTNodeT *recInsert(BSTNodeT *root, char key)
{
    BSTNodeT *p;
    if (root == NULL)
    {
        p = (BSTNodeT *) malloc(sizeof(BSTNodeT));
        p->key = key;
        p->left = p->right = NULL;
        root = p;
        return root;
    }
    else
    {
        if (key < root->key)
            root->left = recInsert(root ->left, key);
        else if (key > root->key)
            root->right = recInsert(root ->right, key);
        else /* key already there */
            printf("\nNode of key=%d already exists\n",
                   key);
    }
    return root;
}
BSTNodeT *find(BSTNodeT *root, int key)
{
    BSTNodeT *p;
    if (root == NULL)
        return NULL;
    p = root;
    while (p != NULL)
    {
        if (p -> key == key)
            return p; /* found */
        else if (key < p->key)
            p = p->left;
        else
            p = p->right;
    }
    return NULL; /* not found */
}
BSTNodeT *delNode(BSTNodeT *root, int key)
{
    BSTNodeT *p; /* points to node to delete */
    BSTNodeT *pParent; /* points to parent of p */
    BSTNodeT *pRepl; /* points to node that will replace p */
    BSTNodeT *pReplParent; /* points to parent of node that will replace p */
    int direction; /* LEFT, RIGHT */
    if (root == NULL)
        return NULL; /* empty tree */
    p = root;
    pParent = NULL;
    while (p != NULL && p->key != key)
    {
        if (key < p->key)
        {
            /* search left branch */
            pParent = p;
            p = p->left;
            direction = LEFT;
        }
        else
        {
            /* search right branch */
            pParent = p;
            p = p->right;
            direction = RIGHT;
        }
    }
    if (p == NULL)
    {
        printf("\nNo node of key value=%d\n", key);
        return root;
    }
    if (p->left == NULL)
        pRepl = p->right; /* no left child */
    else if (p->right == NULL)
        pRepl = p->left; /* no right child */
    else
    {
        /* both children present */
        pReplParent = p;
        pRepl = p->right; /* search right subtree */
        while (pRepl->left != NULL)
        {
            pReplParent = pRepl;
            pRepl = pRepl->left;
        }
        if (pReplParent != p)
        {
            pReplParent->left = pRepl->right;
            pRepl->right = p->right;
        }
        pRepl->left = p->left;
    }
    free(p);
    printf("\nDeletion of node %d completed\n", key);
    if (pParent == NULL)
        return pRepl; /* original root was deleted */
    else
    {
        if (direction == LEFT)
            pParent->left = pRepl;
        else
            pParent->right = pRepl;
        return root;
    }
}
void delTree(BSTNodeT *root)
{
    if (root != NULL)
    {
        delTree(root->left);
        delTree(root->right);
        free(root);
    }
}
int getInt(const char *message)
{
    int val;
    printf(message);
    scanf("%d", &val);
    fflush(stdin);
    return val;
}
char prompt(const char *message)
{
    printf(message);
    char ch = getchar();
    fflush(stdin);
    return ch;
}

command getCommand()
{
    command new_command;
    scanf("\n%c%c",&new_command.verb, &new_command.noun);
    return new_command;
}

char get_largest_node(BSTNodeT *root){
    if(root==NULL){
        prompt("tree is empty");
        return 0;
    }
    if(root->right==NULL){
        return root->key;
    }
    else{
        get_largest_node(root->right);
    }
}

char get_smallest_node(BSTNodeT *root){
    if(root==NULL){
        prompt("tree is empty");
        return 0;
    }
    if(root->left==NULL){
        return root->key;
    }
    else{
        get_smallest_node(root->left);
    }
}

int main(){
    command current_command;
    int n, key;
    root = NULL;
    while(current_command.verb!='X'&&current_command.noun!='X')
    {
        current_command=getCommand();
        switch(current_command.verb)
        {
        case 'i':
            root = recInsert(root, current_command.noun);
            break;
        case 'd':
            root = delNode(root, current_command.noun);
            break;
        case 'f':
            if(find(root, current_command.noun)!=NULL){
                prompt("node is in tree");
            }
            else{
                prompt("node was not found in tree");
            }
            break;
        case 't':
            switch(current_command.noun)
            {
            case 'p':
                preorder(root,0);
                break;
            case 'P':
                postorder(root,0);
                break;
            case 'i':
                inorder(root,0);
                break;
            default:
                prompt("Illegal command\n");
            }
            break;
        case 'g':
            switch(current_command.noun)
            {
            case 'm':
                printf("The smallest letter in the tree is:%c\n",get_smallest_node(root));
                break;
            case 'M':
                printf("The largest letter in the tree is:%c\n",get_largest_node(root));
                break;
            default:
                prompt("Illegal command\n");
            }
            break;
        default:
            prompt("Illegal command\n");
        }
    }


    return 0;
}
