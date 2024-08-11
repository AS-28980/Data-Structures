#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node* left;
    struct node* right;
};
typedef struct node node;

node* create(int key)
{
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

node* search(node* root, int key)
{   
    if(root==NULL || key == root->data)
        return root;
    else if(key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

node* insert(node* root, int key)
{
    if(root == NULL)
        return create(key);
    if(key <= root->data)
        root->left = insert(root->left, key);
    else if(key > root->data)
        root->right = insert(root->right, key);

    return root;
}

node* successor(node* root, int key)
{
    node* current = search(root, key);

    if(current == NULL)
    {
        printf("Node with key %d not present in the tree\n", key);
        return NULL;
    }

    if(current->right != NULL)
    {
        current = current->right;
        while(current->left != NULL)
            current = current->left;
        return current;
    }
    else
    {
        node* successor = NULL;
        node* ancestor = root;
        while(ancestor != current)
        {
            if(current->data < ancestor->data)
            {
                successor = ancestor;
                ancestor = ancestor->left;
            }
            else
                ancestor = ancestor->right;
        }

        return successor;
    }
}

node* min(node* root)
{
    while(root->left != NULL)
        root = root->left;
    return root;
}

node* delete(node* root, int key)
{
    if(root == NULL)
    {
        printf("Node %d not in tree\n\n", key);
        return root;
    }

    if(key < root->data)
        root->left = delete(root->left, key);
    else if(key > root->data)
        root->right = delete(root->right, key);
    else
    {
        if(root->left == NULL)
        {
            node* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL)
        {
            node* temp = root->left;
            free(root);
            return temp;
        }

        node* temp = min(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }

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
    int keys[] = {12, 31, 34, 56, 78, 89, 91, 32, 56, 81, 100, 2, 55, 21, 99, 121, 67};
    int n = sizeof(keys)/sizeof(keys[0]);

    node* root = NULL;

    for(int i=0; i<n; i++)
        root = insert(root, keys[i]);

    printLevelOrder(root);

    printf("Searching:\n");
    node* srch;
    srch = search(root, 32);
    if(srch != NULL)
        printf("%d is present\n", 32);
    else
        printf("%d is absent\n", 32);

    srch = search(root, 56);
    if(srch != NULL)
        printf("%d is present\n", 56);
    else
        printf("%d is absent\n", 56);

    srch = search(root, 90);
    if(srch != NULL)
        printf("%d is present\n\n", 90);
    else
        printf("%d is absent\n\n", 90);

    printf("Tree after insertion:\n");
    root = insert(root, 32);
    root = insert(root, 56);
    root = insert(root, 21);
    root = insert(root, 90);

    printLevelOrder(root);

    printf("Successors:\n");
    node* succ;
    succ = successor(root, 32);
    if(succ != NULL)
        printf("The successor of %d is %d\n", 32, succ->data);
    else
        printf("No successor found for %d\n", 32);
    
    succ = successor(root, 56);
    if(succ != NULL)
        printf("The successor of %d is %d\n", 56, succ->data);
    else
        printf("No successor found for %d\n", 56);

    succ = successor(root, 21);
    if(succ != NULL)
        printf("The successor of %d is %d\n", 21, succ->data);
    else
        printf("No successor found for %d\n", 21);

    succ = successor(root, 90);
    if(succ != NULL)
        printf("The successor of %d is %d\n\n", 90, succ->data);
    else
        printf("No successor found for %d\n\n", 90);

    printf("Deleting:\n");
    delete(root, 332);
    delete(root, 51);
    delete(root, 71);
    delete(root, 67);

    printf("Tree after deletion:\n");
    printLevelOrder(root);
}
