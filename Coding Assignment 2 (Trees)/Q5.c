/*
Write a C program that takes an arithmetic tree as input and outputs
the result of the arithmetic expression. The leaf node is numeric data in
an arithmetic expression tree, and the non-leaf/internal node is the
operator.
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct node
{
    int data;
    struct node* left;
    struct node* right;
};
typedef struct node node;

node* createNode(int data)
{
    node* temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

node* insertLeft(node* root, int data)
{
    root->left = createNode(data);
    return root->left;
}

node* insertRight(node* root, int data)
{
    root->right = createNode(data);
    return root->right;
}

node* search(node* root, int data)
{
    if (root == NULL || (root->data == data && root->left==NULL)) 
    {
        return root;
    }

    node* temp = search(root->left, data);
    if (temp != NULL) 
    {
        return temp;
    }

    return search(root->right, data);
}

int evaluate(node* root)
{
    if(root->left == NULL && root->right == NULL)
        return root->data;
    
    int left = evaluate(root->left);
    int right = evaluate(root->right);

    char c = (char)root->data;

    switch(c)
    {
        case '+':
            return left+right;
        case '-':
            return left-right;
        case '*':
            return left*right;
        case '/':
            if(right==0)
            {
                printf("Error: Division by 0");
                exit(0);
            }
            return left/right;
        case '%':
            return left%right;
        case '^':
            return (int)pow(left, right);
        default:
            printf("Invalid operator: %c\n", root->data);
            exit(0);
    }
}

void printTree(node* root) {
    if (root != NULL) {
        printf("Node: %d\n", root->data);
        printf("Left Child:\n");
        printTree(root->left);
        printf("Right Child:\n");
        printTree(root->right);
    }
}

int main()
{
    printf("Enter number of nodes: ");
    int n;
    scanf("%d", &n);
    int arr[n][3];
    printf("Enter elements(Enter ascii values of operators)\n");
    for(int i=0; i<n; i++)
        scanf("%d %d %d", &arr[i][0], &arr[i][1], &arr[i][2]);
    
    node* root = createNode(arr[0][0]);
    node* temp;

    for(int i=0; i<n; i++)
    {
        temp = search(root, arr[i][0]);
        if(arr[i][1]!=-1 && arr[i][2]!=-1)
        {
            insertLeft(temp, arr[i][1]);
            insertRight(temp, arr[i][2]);
        }
        else if(arr[i][1]==-1 && arr[i][2]==-1)
        {}
        else
        {
            printf("Invalid input");
            exit(0);
        }
    }

    // printTree(root);
    printf("Result: %d", evaluate(root));

}