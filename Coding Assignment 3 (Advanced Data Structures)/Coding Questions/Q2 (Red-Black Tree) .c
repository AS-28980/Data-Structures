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

node* leftRotate(node* x) 
{
    node* y = x->right;
    x->right = y->left;
    y->left = x;
    y->color = x->color;
    x->color = RED;
    return y;
}

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

// Function to search for a value in the Red-Black Tree
bool search(node* root, int data) 
{
    if (root == NULL)
        return false;

    if (data == root->data)
        return true;
    else if (data < root->data)
        return search(root->left, data);
    else
        return search(root->right, data);
}

// Function to find the minimum value in the Red-Black Tree
node* findMinValue(node* root) 
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Function to delete a node from the Red-Black Tree
node* deleteRBNode(node* root, int data) 
{
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteRBNode(root->left, data);
    else if (data > root->data) 
        root->right = deleteRBNode(root->right, data);
    else
    {
        if (root->left == NULL || root->right == NULL) 
        {
            node* temp = (root->left != NULL) ? root->left : root->right;
            if (temp == NULL) 
            {
                temp = root;
                root = NULL;
            } 
            else
                *root = *temp;
                
            free(temp);
        } 
        else 
        {
            node* temp = findMinValue(root->right);
            root->data = temp->data;
            root->right = deleteRBNode(root->right, temp->data);
        }
    }

    if (root == NULL)
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

// Function to delete a value from the Red-Black Tree
RBTree* delete(RBTree* tree, int data) 
{
        tree->root = deleteRBNode(tree->root, data);
        if (tree->root != NULL) 
            tree->root->color = BLACK;
    return tree;
}

// Function to print the Red-Black Tree in level order
void printLevelOrder(node* root) 
{
    if (root == NULL) 
        return;

    node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) 
    {
        int levelSize = rear - front;

        for (int i = 0; i < levelSize; i++) 
        {
            node* current = queue[front++];
            printf("%d ", current->data);

            if (current->left != NULL)
                queue[rear++] = current->left;
            if (current->right != NULL)
                queue[rear++] = current->right;
        }

        printf("\n");
    }
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
    
    int queryChoice;
    int query;

    while(1)
    {
        scanf("%d %d", &queryChoice, &query);
        switch(queryChoice)
        {
            case 1:
            //Search
            if(search(rbTree->root, query))
                printf("%d present\n", query);
            else
                printf("%d not present\n", query);
            break;

            case 2:
            //Insert
            if(search(rbTree->root, query))
                printf("%d already present. So no need to insert\n", query);
            else
            {
                rbTree = insert(rbTree, query);
                printf("%d inserted\n", query);
            }
            break;

            case 3:
            //Delete
            if(search(rbTree->root, query))
            {
                rbTree = delete(rbTree, query);
                printf("%d deleted\n", query);
            }
            else
                printf("%d not present. So it can not be deleted\n", query);
            break;

            case 4:
            //Print
            printLevelOrder(rbTree->root);
            break;

            default:
                printf("Invalid Input. Try again\n");
        }
    }
    free(elements);

    return 0;
}
