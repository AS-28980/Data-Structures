/*
Write a C program that prints the given tree vertically. The following
example explains the vertical tree traversal.
*/
#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int data;
    struct node* left;
    struct node* right;
};
typedef struct node node;

struct listNode 
{
    int data;
    struct listNode* next;
};
typedef struct listNode lNode;

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
    node* temp = createNode(data);
    root->left = temp;
    return temp;
}

node* insertRight(node* root, int data) 
{
    node* temp = createNode(data);
    root->right = temp;
    return temp;
}

node* search(node* root, int data) 
{
    if (root == NULL || root->data == data) 
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

int pos(node* root, int key) 
{
    if(root->data == key)
        return 0;
    if(search(root->left, key) != NULL)
        return (pos(root->left, key)-1);
    if(search(root->right, key) != NULL)
        return (pos(root->right, key)+1);
}

void insertInLinkedList(lNode* head, int data)
{
    lNode* temp = (lNode*)malloc(sizeof(lNode));
    temp->data = data;
    temp->next = NULL;
    while(head->next != NULL)
        head = head->next;
    head->next = temp;
}

void printList(lNode* head)
{
    while(head->next != NULL)
    {
        printf("%d, ", head->data);
        head = head->next;
    }
    printf("%d\n", head->data);
}

int main() 
{
    printf("Enter no. of elements: ");
    int n;
    scanf("%d", &n);
    printf("Enter n rows (data left right) [Check specifications in readme]:\n");
    int arr[n][3];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &arr[i][0], &arr[i][1], &arr[i][2]);
    }

    node* root = createNode(arr[0][0]);
    node* temp;
    for (int i = 0; i < n; i++) 
    {
        temp = search(root, arr[i][0]);
        if (arr[i][1] != -1)
            insertLeft(temp, arr[i][1]);
        if (arr[i][2] != -1)
            insertRight(temp, arr[i][2]);
    }

    int lmax = 0, rmax = 0, t = 0;

    for (int i = 0; i < n; i++) 
    {
        t = pos(root, arr[i][0]);
        if (t < lmax)
            lmax = t;
        if (t > rmax)
            rmax = t;
    }

    lNode* hashtable[rmax + 1 - lmax];

    for(int i=0; i<(rmax+1-lmax); i++)
        hashtable[i] = NULL;
    
    for(int i=0; i<n; i++)
    {
        t = pos(root, arr[i][0]);

        if(hashtable[t-lmax] == NULL)
        {
            lNode* temp = (lNode*)malloc(sizeof(lNode));
            temp->data = arr[i][0];
            temp->next = NULL;
            hashtable[t-lmax] = temp;
        }
        else
            insertInLinkedList(hashtable[t-lmax], arr[i][0]);
    }    

    printf("\nVertical order traversal is:\n");
    char letters[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for(int i=0; i<(rmax+1-lmax); i++)
    {
        printf("%c- ", letters[i]);
        printList(hashtable[i]);
    }
    return 0;
}

