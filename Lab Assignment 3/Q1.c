#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node* left;
    struct node* right;
};
typedef struct node node;

node* create(int data) 
{
  node* newNode = (node*)malloc(sizeof(struct node));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

node* insertLeft(node* root, int data) 
{
  root->left = create(data);
  return root->left;
}

node* insertRight(node* root, int data)
{
    root->right = create(data);
    return root->right;
}

void preOrderTraversal(node* root) 
{
    if (root == NULL) 
        return;
    printf("%d ", root->data);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void inOrderTraversal(node* root) 
{
    if (root == NULL) 
        return;
    inOrderTraversal(root->left);
    printf("%d ", root->data);
    inOrderTraversal(root->right);
}

void postOrderTraversal(node* root) 
{
    if (root == NULL) 
        return;
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    printf("%d ", root->data);
}

node* search(node* root, int data)
{
    if (root == NULL)
        return NULL;
    if (root->data == data)
        return root;

    node* left = search(root->left, data);
    if (left != NULL)
        return left;

    node* right = search(root->right, data);
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

    node* root = create(arr[0][0]);
    node* temp;
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

// Sample test case
// 5 2 1
// 2 3 4
// 1 100 200
// 3 7 -1
// 4 18 26
// 100 -1 300
// 200 45 -1
// 7 -1 -1
// 18 -1 -1
// 26 -1 35
// 300 -1 -1
// 45 -1 69
// 35 -1 -1
// 69 -1 -1
// Preorder traversal: 5 2 3 7 4 18 26 35 1 100 300 200 45 69

// Inorder traversal: 7 3 2 18 4 26 35 5 100 300 1 45 69 200

// Postorder traversal: 7 3 18 35 26 4 2 300 100 69 45 200 1 5
//Solutions were verified by calculating by hand