#include <stdio.h>
#include <stdlib.h>
typedef struct node_type
{
    char id; /* node name */
    /* ... other useful info */
    struct node_type *left, *right;
} NodeT;
void fatalError( const char *msg )
{
    printf( msg );
    printf( "\n" );
    exit ( 1 );
}
void preorder( NodeT *p, int level )
{
    if ( p != NULL )
    {
        for ( int i = 0; i <= level; i++ )
            printf( " " ); /* for nice listing */
        printf( "%2.2d\n", p->id );
        preorder( p->left, level + 1 );
        preorder( p->right, level + 1 );
    }
}
void inorder( NodeT *p, int level )
{
    if ( p != NULL )
    {
        inorder( p->left, level + 1 );
        for ( int i = 0; i <= level; i++ )
            printf( " " ); /* for nice listing */
        printf( "%2.2d\n", p->id );
        inorder( p->right, level + 1 );
    }
}
void postorder( NodeT *p, int level )
{
    if ( p != NULL )
    {
        postorder( p->left, level + 1 );
        postorder( p->right, level + 1 );
        for ( int i = 0; i <= level; i++ )
            printf( " " ); /* for nice listing */
        printf( "%2.2d\n", p->id );
    }
}
NodeT *createBinTree( int branch, NodeT *parent )
{
    NodeT *p;
    int id;
    /* read node id */
    if ( branch == 0 )
        printf( "Root identifier [0 to end] =" );
    else if ( branch == 1 )
        printf( "Left child of %d [0 to end] =",
                parent->id );
    else
        printf( "Right child of %d [0 to end] =",
                parent->id );
    scanf("%d", &id);
    if ( id == 0 )
        return NULL;
    else
    {
        /* build node pointed to by p */
        p = ( NodeT *)malloc(sizeof( NodeT ));
        if ( p == NULL )
            fatalError( "Out of space in createBinTree" );
        /* fill in node */
        p->id = id;
        p->left = createBinTree( 1, p );
        p->right = createBinTree( 2, p );
    }
    return p;
}

int leaf_number(NodeT *root)
{   if(root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    else
    {
        int left_leaves = leaf_number(root->left);
        int right_leaves = leaf_number(root->right);
        return left_leaves + right_leaves;
    }
}

int main()
{
    NodeT *root = createBinTree( 0, NULL );
    while ('\n' != getc(stdin));
    printf("%d", leaf_number(root));
    return 0;
}
