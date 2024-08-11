/*
Write a non-recursive implementation of inorder, preorder, postorder
traversal.
*/
#include<stdio.h>
#include<stdlib.h>
#define MAXLEN 1000

struct TreeNode
{
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};
typedef struct TreeNode tnode;

struct StackNode
{
    tnode *node;
    struct StackNode *next;
};
typedef struct StackNode snode;


tnode* create(int data) 
{
  tnode* newNode = (tnode*)malloc(sizeof(tnode));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

tnode* insertLeft(tnode* root, int data) 
{
  root->left = create(data);
  return root->left;
}

tnode* insertRight(tnode* root, int data)
{
    root->right = create(data);
    return root->right;
}

void push(snode** stack, tnode* node) 
{
    snode* newNode = (snode*)malloc(sizeof(snode));
    newNode->node = node;
    newNode->next = *stack;
    *stack = newNode;
}

tnode* pop(snode** stack) 
{
    if (*stack == NULL)
        return NULL;
    snode* temp = *stack;
    *stack = (*stack)->next;
    snode* poppedNode = temp->node;
    free(temp);
    return poppedNode;
}

int isEmpty(snode* stack) {
    return stack == NULL;
}

void preOrderTraversal(tnode* root) 
{
    if (root == NULL) 
        return;
    tnode* current = root;
    snode* stack = NULL;

    push(&stack, current);

    while(!isEmpty(stack))
    {
        current = pop(&stack);
        printf("%d ", current->data);

        if(current->right != NULL)
            push(&stack, current->right);
        if(current->left != NULL)
            push(&stack, current->left);
    }
}

void inOrderTraversal(tnode* root) 
{
    if(root == NULL)
        return;
    tnode* current = root;
    snode* stack = NULL;

    while(current != NULL || !isEmpty(stack))
    {
        while(current != NULL)
        {
            push(&stack, current);
            current = current->left;
        }
        current = pop(&stack);
        printf("%d ", current->data);
        current = current->right;
    }

    
}

void postOrderTraversal(tnode* root) 
{
    if (root == NULL) 
        return;
    tnode* current = root;

    snode* stack1 = NULL;
    snode* stack2 = NULL;
    push(&stack1, root);

    while (!isEmpty(stack1)) 
    {
        current = pop(&stack1);
        push(&stack2, current);

        if (current->left)
            push(&stack1, current->left);
        if (current->right)
            push(&stack1, current->right);
    }

    while (!isEmpty(stack2)) 
    {
        printf("%d ", pop(&stack2)->data);
    }
}

tnode* search(tnode* root, int data)
{
    if (root == NULL)
        return NULL;
    if (root->data == data)
        return root;

    tnode* left = search(root->left, data);
    if (left != NULL)
        return left;

    tnode* right = search(root->right, data);
    if (right != NULL)
        return right;

    return NULL;
}


int main()
{
    printf("Enter number of elements: ");
    int n;
    scanf("%d", &n);

    int arr[n][3];
    printf("For each row, enter the value of the node, followed by its left child and then its right child. If either is absent, enter -1\n");

    for(int i=0; i<n; i++)
    {
        scanf("%d %d %d", &arr[i][0], &arr[i][1], &arr[i][2]);
    }

    tnode* root = create(arr[0][0]);
    tnode* temp;
    for(int i=0; i<n; i++)
    {
        temp = search(root, arr[i][0]);
        if(arr[i][1]!=-1)
        {
            insertLeft(temp, arr[i][1]);
        }
        if(arr[i][2]!=-1)
        {
            insertRight(temp, arr[i][2]);
        }
    }
    printf("Preorder traversal: ");
    preOrderTraversal(root);
    printf("\n\n");

    printf("Inorder traversal: ");
    inOrderTraversal(root);
    printf("\n\n");

    printf("Postorder traversal: ");
    postOrderTraversal(root);
    printf("\n\n");   
}