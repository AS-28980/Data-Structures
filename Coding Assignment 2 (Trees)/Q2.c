/*
Write a C program that takes inorder and preorder traversal as input,
output the tree. You need to print the nodes of the tree level by level.
Your code should output an error message if the inorder and preorder
are not corresponding to the same tree.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXLEN 100

struct result 
{
    int* ptr;
    int size;
};

struct result* convertToIntArray(char str[]) 
{
    int* arr = (int*)malloc(MAXLEN * sizeof(int));
    int index = 0, i = 0;
    int sign = 1;
    int num = 0;

    while (str[i] != '\0') 
    {
        if (str[i] == ' ') 
        {
            arr[index] = sign * num;
            num = 0;
            index++;
            sign = 1;
            i++;
        } 
        else if (str[i] == '-') 
        {
            sign = -1;
            i++;
        } 
        else if (str[i] >= '0' && str[i] <= '9') 
        {
            num = num * 10 + (str[i] - '0');
            i++;
        } 
        else 
        {
            printf("Invalid input\n");
            free(arr);
            exit(0);
        }
    }
    arr[index] = sign * num;

    int* array = (int*)realloc(arr, (index + 1) * sizeof(int));
    struct result* res = (struct result*)malloc(sizeof(struct result));
    res->ptr = array;
    res->size = index + 1;
    return res;
}

struct node
{
    int data;
    struct node* left;
    struct node* right;
};
typedef struct node node;

node* createNode(int data)
{
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
  
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) 
    {
        if (L[i] <= R[j]) 
        {
            arr[k] = L[i];
            i++;
        }
        else 
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
  
    while (i < n1) 
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) 
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
  
void mergeSort(int arr[], int l, int r)
{
    if (l < r) 
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
  
        merge(arr, l, m, r);
    }
}

void isPossibleTree(int* preorder, int* inorder, int preSize, int inSize)
{
    if(preSize != inSize)
    {
        printf("Invalid input");
        exit(0);
    }

    int pre[preSize];
    for(int i=0; i<preSize; i++)
        pre[i]=preorder[i];
    int in[inSize];
    for(int i=0; i<inSize; i++)
        in[i]=inorder[i];

    mergeSort(pre, 0, preSize-1);
    mergeSort(in, 0, inSize-1);

    for(int i=0; i<preSize; i++)
    {
        if(pre[i] != in[i])
        {
            printf("Invalid input");
            exit(0);
        }
    }
}

node* buildTree(int* preorder, int* inorder, int preSize, int inSize)
{
    isPossibleTree(preorder, inorder, preSize, inSize);
    if (preSize == 0)
        return NULL;

    node* root = createNode(preorder[0]);
    int i = 0;

    while (inorder[i] != preorder[0])
        i++;

    root->left = buildTree(preorder + 1, inorder, i, i);
    root->right = buildTree(preorder + i + 1, inorder + i + 1, preSize - i - 1, preSize - i - 1);

    return root;
}

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
    printf("\n");
}

int main() 
{
    printf("Enter preorder expression: ");
    char pre[MAXLEN];
    fgets(pre, sizeof(pre), stdin);
    if(pre[strlen(pre)-1] == '\n')
        pre[strlen(pre)-1] = '\0';

    printf("Enter inorder expression: ");
    char in[MAXLEN];
    fgets(in, sizeof(in), stdin);
    if(in[strlen(in)-1] == '\n')
        in[strlen(in)-1] = '\0';
    
    struct result* res;
    res = convertToIntArray(pre);
    int* preorder = res->ptr;
    int preSize = res->size;
    res = convertToIntArray(in);
    int* inorder = res->ptr;
    int inSize = res->size;

    node* root = buildTree(preorder, inorder, preSize, inSize);
    printLevelOrder(root);
}
