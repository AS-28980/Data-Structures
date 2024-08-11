/*
Write a C program that takes preorder and postorder traversal as
input, output the tree. It is given that each node consists of exactly two
children. Your code should output an error message if the inorder and
preorder are not corresponding to the same tree. You need to print the
nodes of the tree level by level.
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

void isPossibleTree(int* preorder, int* postorder, int preSize, int postSize)
{
    if(preSize != postSize)
    {
        printf("Invalid input");
        exit(0);
    }

    int pre[preSize];
    for(int i=0; i<preSize; i++)
        pre[i]=preorder[i];
    int post[postSize];
    for(int i=0; i<postSize; i++)
        post[i]=postorder[i];

    mergeSort(pre, 0, preSize-1);
    mergeSort(post, 0, postSize-1);

    for(int i=0; i<postSize; i++)
    {
        if(pre[i] != post[i])
        {
            printf("Invalid input");
            exit(0);
        }
    }
}
node* buildTree(int* preorder, int* postorder, int preSize, int postSize)
{
    isPossibleTree(preorder, postorder, preSize, postSize);
    if (preSize == 0)
        return NULL;
    if (preSize == 1)
        return createNode(preorder[0]);
    node* root = createNode(preorder[0]);
    int i=0;

    while(preorder[i] != postorder[preSize-2])
        i++;
    
    root->left = buildTree(preorder + 1, postorder, i-1, i-1);
    root->right = buildTree(preorder + i , postorder + i - 1, preSize - i, preSize - i);

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

    printf("Enter postorder expression: ");
    char post[MAXLEN];
    fgets(post, sizeof(post), stdin);
    if(post[strlen(post)-1] == '\n')
        post[strlen(post)-1] = '\0';
    
    struct result* res;
    res = convertToIntArray(pre);
    int* preorder = res->ptr;
    int preSize = res->size;
    res = convertToIntArray(post);
    int* postorder = res->ptr;
    int postSize = res->size;

    node* root = buildTree(preorder, postorder, preSize, postSize);
    printLevelOrder(root);
}