#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int data;
    int height;
    struct node* left;
    struct node* right;
};
typedef struct node node;

int height(node* n)
{
    if (n == NULL)
        return 0;
    return n->height;
}

int LRDiff(node* n) //Calculates height diff between left and right subtrees
{
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

void updateHeight(node* n) // Function to update height of a node after insertion/deletion
{
    if (n == NULL)
        return;
    int left_height = height(n->left);
    int right_height = height(n->right);
    n->height = (left_height > right_height ? left_height : right_height) + 1;
}

node* type1Rotate(node* y) //A node is rotated with its left child
{
    node* x = y->left;
    node* temp = x->right;

    x->right = y;
    y->left = temp;

    updateHeight(y);
    updateHeight(x);

    return x;
}

node* type2Rotate(node* x) //A node is rotated with its right child
{
    node* y = x->right;
    node* temp = y->left;

    y->left = x;
    x->right = temp;

    updateHeight(x);
    updateHeight(y);

    return y;
}

node* insert(node* root, int key)
{
    if (root == NULL)
    {
        node* new_node = (node *)malloc(sizeof(node));
        new_node->data = key;
        new_node->height = 1;
        new_node->left = new_node->right = NULL;
        return new_node;
    }

    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);

    /*
    Since the insert function is returning the root node,
    the updateHeight function also gets called recursively.
    Essentially, on insertion, the height of every ancestor of the inserted
    node is updated recursively. Whenever an imbbalance is seen,
    Rotation takes place to handle it
    */

    updateHeight(root);

    int diff = LRDiff(root); // Calculating the diff after updating height

    if (diff > 1)
    {
        if (key < root->left->data)
            return type1Rotate(root);
        else
        {
            root->left = type2Rotate(root->left);
            return type1Rotate(root);
        }
    }

    if (diff < -1)
    {
        if (key > root->right->data)
            return type2Rotate(root);
        else
        {
            root->right = type1Rotate(root->right);
            return type2Rotate(root);
        }
    }

    return root;
}

node* delete(node* root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = delete(root->left, key);
    else if (key > root->data)
        root->right = delete(root->right, key);
    else
    {
        if (root->left == NULL)
        {
            node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            node* temp = root->left;
            free(root);
            return temp;
        }

        node* min_right = root->right;
        while (min_right->left != NULL)
            min_right = min_right->left;

        root->data = min_right->data;
        root->right = delete(root->right, min_right->data);
    }

    updateHeight(root);

    int diff = LRDiff(root);

    if (diff > 1)
    {
        if (LRDiff(root->left) >= 0)
        {
            root = type1Rotate(root);
            return root; // Update the root after rotation
        }
        else
        {
            root->left = type2Rotate(root->left);
            root = type1Rotate(root);
            return root; // Update the root after rotation
        }
    }

    if (diff < -1)
    {
        if (LRDiff(root->right) <= 0)
        {
            root = type2Rotate(root);
            return root; // Update the root after rotation
        }
        else
        {
            root->right = type1Rotate(root->right);
            root = type2Rotate(root);
            return root; // Update the root after rotation
        }
    }

    return root;
}

node* search(node* root, int key)
{
    if (root == NULL)
        return NULL;
    if (key == root->data)
        return root;
    if (key < root->data)
        return search(root->left, key);
    return search(root->right, key);
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
}

int main()
{
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

    node* root = NULL;

    for(int i=0; i<n; i++)
        root = insert(root, elements[i]);
    
    int queryChoice;
    int query;

    while(1)
    {
        scanf("%d %d", &queryChoice, &query);
        switch(queryChoice)
        {
            case 1:
            //Search
            if(search(root, query))
                printf("%d present\n", query);
            else
                printf("%d not present\n", query);
            break;

            case 2:
            //Insert
            if(search(root, query))
                printf("%d already present. So no need to insert\n", query);
            else
            {
                root = insert(root, query);
                printf("%d inserted\n", query);
            }
            break;

            case 3:
            //Delete
            if(search(root, query))
            {
                root = delete(root, query);
                printf("%d deleted\n", query);
            }
            else
                printf("%d not present. So it can not be deleted\n", query);
            break;

            case 4:
            //Print
            printLevelOrder(root);
            break;

            default:
                printf("Invalid Input. Try again\n");
        }
    }
    free(elements);

    return 0;
}
