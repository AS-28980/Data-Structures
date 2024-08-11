#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct RBTreeNode 
{
    int data;
    bool color;
    struct RBTreeNode* left;
    struct RBTreeNode* right;
};

#define RED true
#define BLACK false

typedef struct RBTreeNode node;

node* createnode(int data) 
{
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->color = RED; // Initially, new nodes are red
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Red-Black Tree Data Structure
struct RBTree 
{
    node* root;
};

typedef struct RBTree RBTree;

// Function to left rotate the Red-Black Tree
node* leftRotate(node* x) 
{
    node* y = x->right;
    x->right = y->left;
    y->left = x;
    y->color = x->color;
    x->color = RED;
    return y;
}

// Function to right rotate the Red-Black Tree
node* rightRotate(node* y) 
{
    node* x = y->left;
    y->left = x->right;
    x->right = y;
    x->color = y->color;
    y->color = RED;
    return x;
}

// Function to flip the colors of a node and its children
void flipColors(node* node) 
{
    node->color = !node->color;
    node->left->color = !node->left->color;
    node->right->color = !node->right->color;
}

// Function to insert a new node into the Red-Black Tree
node* insertRBNode(node* root, int data) 
{
    if (root == NULL)
        return createnode(data);

    // Standard BST insertion
    if (data < root->data) 
        root->left = insertRBNode(root->left, data);
    else if (data > root->data) 
        root->right = insertRBNode(root->right, data);
    else
        return root;

    // Fix any violations and balance the tree
    if (root->right != NULL && root->right->color)
        root = leftRotate(root);

    if (root->left != NULL && root->left->color && root->left->left != NULL && root->left->left->color)
        root = rightRotate(root);

    if (root->left != NULL && root->left->color && root->right != NULL && root->right->color)
        flipColors(root);

    return root;
}

// Function to insert a value into the Red-Black Tree
RBTree* insert(RBTree* tree, int data) 
{
    tree->root = insertRBNode(tree->root, data);
    tree->root->color = BLACK; // The root should always be black
    return tree;
}

void RB_ENUMERATE(node* x, int a, int b) 
{
    if(x == NULL)
        return;
    if(a <= x->data && x->data <= b)
        printf("%d ", x->data);
    if(a <= x->data)
        RB_ENUMERATE(x->left, a, b);
    if(x->data <= b)
        RB_ENUMERATE(x->right, a, b);
    return;
}
// Main function
int main() 
{
    RBTree* rbTree = (RBTree*)malloc(sizeof(RBTree));
    rbTree->root = NULL;

    int n;
    char input[1000];
    int *elements;

    scanf("%d", &n);

    elements = (int *)malloc(n * sizeof(int));

    scanf(" %[^\n]s", input);

    char *token = strtok(input, " ");
    int i = 0;

    while (token != NULL && i < n) 
    {
        elements[i] = atoi(token);
        token = strtok(NULL, " ");
        i++;
    }


    for(int i=0; i<n; i++)
        rbTree = insert(rbTree, elements[i]);

    int a,b;
    printf("Enter a(Lower Bound): ");
    scanf("%d", &a);
    printf("Enter b(Upper Bound): ");
    scanf("%d", &b);
    RB_ENUMERATE(rbTree->root, a, b);
    
    free(elements);

    return 0;
}
