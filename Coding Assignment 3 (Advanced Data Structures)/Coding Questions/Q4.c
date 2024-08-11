#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX 9
#define MIN 4

#define t (MAX-MIN)

struct BTreeNode 
{
    bool isLeaf;
    int count;
    int key[2*t-1];
    struct BTreeNode* children[2*t];
};
typedef struct BTreeNode node;

struct Btree 
{
    node* bRoot;
};
typedef struct Btree Btree;

Btree* createBtree() 
{
    Btree* btree = (Btree*)malloc(sizeof(Btree));
    btree->bRoot = NULL;
    return btree;
}

bool search(node* x, int k) 
{
    if (x == NULL) 
        return false;

    int i = 0;
    while (i < x->count && k > x->key[i])
        i++;

    if (i < x->count && k == x->key[i])
        return true;
    else if (x->isLeaf)
        return false;
    else
        return search(x->children[i], k);
}

node* splitChild(node* x, int i, node* y) 
{
    node* z = (node*)malloc(sizeof(node));
    z->isLeaf = y->isLeaf;
    z->count = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->key[j] = y->key[j + t];

    if (!y->isLeaf) 
    {
        for (int j = 0; j < t; j++)
            z->children[j] = y->children[j + t];
    }

    y->count = t - 1;

    for (int j = x->count; j >= i + 1; j--)
        x->children[j + 1] = x->children[j];

    x->children[i + 1] = z;

    for (int j = x->count - 1; j >= i; j--)
        x->key[j + 1] = x->key[j];

    x->key[i] = y->key[t - 1];
    x->count++;

    return x;
}

node* insertNonFull(node* x, int k) 
{
    int i = x->count - 1;
    if (x->isLeaf) 
    {
        while (i >= 0 && k < x->key[i]) 
        {
            x->key[i + 1] = x->key[i];
            i--;
        }
        x->key[i + 1] = k;
        x->count++;
    } 
    else 
    {
        while (i >= 0 && k < x->key[i])
            i--;
        i++;
        if (x->children[i]->count == 2*t-1) 
        {
            x = splitChild(x, i, x->children[i]);
            if (k > x->key[i])
                i++;
        }
        x->children[i] = insertNonFull(x->children[i], k);
    }
    return x;
}

node* insert(node* x, int k) 
{
    if (x == NULL) 
    {
        node* root = (node*)malloc(sizeof(node));
        root->isLeaf = true;
        root->count = 1;
        root->key[0] = k;
        root->children[0] = NULL;
        return root;
    }

    if (x->count == 2*t-1) 
    {
        node* newRoot = (node*)malloc(sizeof(node));
        newRoot->isLeaf = false;
        newRoot->count = 0;
        newRoot->children[0] = x;
        newRoot = splitChild(newRoot, 0, x);
        newRoot = insertNonFull(newRoot, k);
        return newRoot;
    } 
    else 
        return insertNonFull(x, k);
}

int findMin(node* x) 
{
    while (x->children[0] != NULL)
        x = x->children[0];
    return x->key[0];
}

// Function to move a key from the left sibling to the current node
node* moveKeyFromLeftSibling(node* x, int i) 
{
    node* child = x->children[i];
    node* leftSibling = x->children[i - 1];

    // Make space for the key from the left sibling
    for (int j = child->count; j > 0; j--) 
        child->key[j] = child->key[j - 1];

    child->key[0] = x->key[i - 1];

    // If the child is not a leaf node, move the last child of the left sibling to the child
    if (!child->isLeaf) 
    {
        for (int j = child->count + 1; j > 0; j--)
            child->children[j] = child->children[j - 1];

        child->children[0] = leftSibling->children[leftSibling->count];
    }

    // Update the current node with the key from the left sibling
    x->key[i - 1] = leftSibling->key[leftSibling->count - 1];

    // Update the counts of keys in the child and left sibling
    child->count++;
    leftSibling->count--;

    return x;
}

node* moveKeyFromRightSibling(node* x, int i) {
    node* child = x->children[i];
    node* rightSibling = x->children[i + 1];

    child->key[child->count] = x->key[i];

    if (!child->isLeaf) 
        child->children[child->count + 1] = rightSibling->children[0];

    x->key[i] = rightSibling->key[0];

    for (int j = 0; j < rightSibling->count - 1; j++) 
        rightSibling->key[j] = rightSibling->key[j + 1];

    if (!rightSibling->isLeaf) 
    {
        for (int j = 0; j < rightSibling->count; j++) 
            rightSibling->children[j] = rightSibling->children[j + 1];
    }

    child->count++;
    rightSibling->count--;

    return x;
}

// Function to merge a child node with its sibling
node* merge(node* x, int i) 
{
    node* child = x->children[i];
    node* sibling = x->children[i + 1];

    // Move the key from the current node to the child
    child->key[t - 1] = x->key[i];

    // Copy keys from the sibling to the child
    for (int j = 0; j < t - 1; j++) 
        child->key[t + j] = sibling->key[j];

    // If the child is not a leaf node, copy child pointers from the sibling to the child
    if (!child->isLeaf) 
    {
        for (int j = 0; j < t; j++) 
            child->children[t + j] = sibling->children[j];
    }

    // Shift keys and child pointers in the current node
    for (int j = i; j < x->count - 1; j++) 
    {
        x->key[j] = x->key[j + 1];
        x->children[j + 1] = x->children[j + 2];
    }

    // Update counts of keys in the current node and child
    x->count--;
    child->count += t - 1;

    // Free the sibling node
    free(sibling);

    return x;
}

// Function to find the predecessor key in a B-tree node
int Pred(node* x, int i) 
{
    node* current = x->children[i];
    while (!current->isLeaf) 
        current = current->children[current->count];
    
    return current->key[current->count - 1];
}

// Function to find the successor key in a B-tree node
int Succ(node* x, int i) 
{
    node* current = x->children[i + 1];
    while (!current->isLeaf) 
        current = current->children[0];

    return current->key[0];
}

int findKey(node* x, int k) 
{
    int idx = 0;
    while (idx < x->count && k > x->key[idx]) 
        idx++;

    return idx;
}

// Function to delete a key from the B-tree
node* delete(node* x, int k) 
{
    int pos = findKey(x, k);

    // Case 1: The key k is present in the current node x
    if (pos < x->count && x->key[pos] == k) 
    {
        if (x->isLeaf) 
        {
            // Case 1a: If k is in a leaf node and x has more than t-1 keys, delete the key k
            for (int i = pos + 1; i < x->count; ++i)
                x->key[i - 1] = x->key[i];
            
            x->count--;
            return x;
        }

        // Case 1b: If k is in an internal node x and has two children C1 and C2, replace k 
        // with the predecessor of k in the sub-tree rooted at C1, and recursively delete the predecessor from C1
        if (!x->isLeaf) 
        {
            if (x->children[pos]->count >= t) 
            {
                int pred = Pred(x, pos);
                x->key[pos] = pred;
                x->children[pos] = delete(x->children[pos], pred);
            } 
            else if (x->children[pos + 1]->count >= t) 
            {
                int succ = Succ(x, pos);
                x->key[pos] = succ;
                x->children[pos + 1] = delete(x->children[pos + 1], succ);
            } 
            else 
            {
                // Case 1c: If both C1 and C2 have only t-1 keys, merge k and all of C2 into C1
                x = merge(x, pos);
                x->children[pos] = delete(x->children[pos], k);
            }
        }
    } 
    else 
    {
        // Case 2: The key k is not present in the current node x
        if (x->isLeaf)
            // The key k is not present in the tree
            return x;

        // Determine the child C[i] that must contain k, if k is in the tree at all
        int i = 0;
        while (i < x->count && k > x->key[i])
            i++;

        /* Case 2a: If the child C[i] has only t-1 keys but has an immediate sibling 
           with at least t keys, give C[i] an extra key by moving a key from the current node x down into C[i],
           moving a key from C[i]'s immediate left or right sibling up into x, and moving the 
          appropriate child pointer from the sibling into C[i] */
        if (x->children[i]->count == t - 1) 
        {
            if (i > 0 && x->children[i - 1]->count >= t)
                x = moveKeyFromLeftSibling(x, i);
            else if (i < x->count && x->children[i + 1]->count >= t)
                x = moveKeyFromRightSibling(x, i);
        }

        // Case 2b: If C[i] and its immediate siblings have t-1 keys, merge C[i] with one sibling, 
        // which involves moving a key from the current node x down into the merged node
        if (x->children[i]->count == t - 1) 
        {
            if (i > 0) 
            {
                x = merge(x, i - 1);
                i--;
            } 
            else
                x = merge(x, i);
        }

        // Recursively delete the key k from the appropriate child C[i]
        x->children[i] = delete(x->children[i], k);
    }

    return x;
}

// Function to print the B-tree
void printBtree(node* root) 
{
    if (root == NULL) 
    {
        printf("B-tree is empty.\n");
        return;
    }

    node* queue[100]; 
    int front = 0, rear = 0;
    int currentLevelNodes = 1, nextLevelNodes = 0;

    queue[rear++] = root;

    while (front < rear) 
    {
        node* node = queue[front++];
        currentLevelNodes--;

        for (int i = 0; i < node->count; i++)
            printf("%d ", node->key[i]);

        if (!node->isLeaf) 
        {
            for (int i = 0; i <= node->count; i++) 
            {
                queue[rear++] = node->children[i];
                nextLevelNodes++;
            }
        }

        if (currentLevelNodes == 0) 
        {
            printf("\n"); // Move to the next line for the next level
            currentLevelNodes = nextLevelNodes;
            nextLevelNodes = 0;
        }
    }
}

int main() 
{
    Btree* btree = createBtree();
    int n, queryChoice, query;

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
        btree->bRoot = insert(btree->bRoot, elements[i]);

    while(1) 
    {
        scanf("%d %d", &queryChoice, &query);

        switch (queryChoice) 
        {
            case 1:
                if (search(btree->bRoot, query))
                    printf("%d present\n", query);
                else 
                    printf("%d not present\n", query);
                break;

            case 2:
                if(search(btree->bRoot, query))
                    printf("%d already present. So no need to insert\n", query);
                else
                {
                    btree->bRoot = insert(btree->bRoot, query);
                    printf("%d inserted\n", query);
                }
                break;

            case 3:
                if(search(btree->bRoot, query))
                {
                    btree->bRoot = delete(btree->bRoot, query);
                    printf("%d deleted\n", query);
                }
                else
                    printf("%d not present. So it can not be deleted\n", query);
                break;

            case 4:
                if (btree->bRoot != NULL) 
                    printBtree(btree->bRoot);
                else
                    printf("B-tree is empty\n");
                break;

            default:
                printf("Invalid queryChoice. Please enter a valid option.\n");
                break;
        }
    }

    return 0;
}
