#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    int height;
    struct node *left;
    struct node *right;
    struct node *parent;
};
typedef struct node node;

/*
    Note that the logic for both insertion and deletion look very similar to that of a normal
    BST. The only diff is checking whether the AVL property is satisfied on each insertion/deletion.
    Since the functions are all defined recursively, it allows every ancestor to be checked for imbalance.
    On encountering one, it is taken care of immediately using rotation functions.

    Note 2: The pointer to parent within the struct is unnecessary. Ignoring its existence would
    have no impact on the code. 
*/

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
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->parent = NULL;
        return new_node;
    }

    if (key <= root->data)
    {
        root->left = insert(root->left, key);
        root->left->parent = root;
    }
    else if (key > root->data)
    {
        root->right = insert(root->right, key);
        root->right->parent = root;
    }

    updateHeight(root);

    /*
    Since the insert function is returning the root node,
    the updateHeight function also gets called recursively.
    Essentially, on insertion, the height of every ancestor of the inserted
    node is updated recursively. Whenever an imbbalance is seen,
    Rotation takes place to handle it
    */

    int diff = LRDiff(root); //Calculating the diff after updating height

    if (diff > 1)
    {
        if (key <= root->left->data)
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

node* search(node* root, int key)
{
    if (root == NULL)
    {
        printf("Error: Key %d not found\n", key);
        return NULL;
    }
    if (key == root->data)
        return root;
    if (key < root->data)
        return search(root->left, key);
    return search(root->right, key);
}

node* delete(node* root, int key)
{
    if (root == NULL)
    {
        printf("Error: Key %d not found\n", key);
        return root;
    }

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
            return type1Rotate(root);
        else
        {
            root->left = type2Rotate(root->left);
            return type1Rotate(root);
        }
    }

    if (diff < -1)
    {
        if (LRDiff(root->right) <= 0)
            return type2Rotate(root);
        else
        {
            root->right = type1Rotate(root->right);
            return type2Rotate(root);
        }
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
    node *root = NULL;

    int keys[] = {9, 8, 5, 4, 99, 78, 31, 34, 89, 90, 21, 23, 45, 77, 88, 112, 32};
    int num_keys = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < num_keys; i++)
    {
        root = insert(root, keys[i]);
    }

    printf("AVL Tree after insertion:\n");
    printLevelOrder(root);

    printf("\nSearching for nodes:\n");

    if (search(root,32))
        printf("Node 32 found\n");
    if (search(root,56))
        printf("Node 56 found\n");
    if (search(root,90))
        printf("Node 90 found\n");

    int insertKeys[] = {32, 56, 21, 90};
    for(int i=0; i<4; i++)
    {
        root = insert(root, insertKeys[i]);   
    }
    
    printLevelOrder(root);

    int deleteKeys[] = {332, 51, 71, 67};

    printf("\nDeleting nodes:\n");
    for (int i = 0; i < 10; i++)
    {
        root = delete(root, deleteKeys[i]);
        printf("Deleted node %d\n", deleteKeys[i]);
    }

    printf("\nAVL Tree after deletion:\n");
    printLevelOrder(root);

    return 0;
}
