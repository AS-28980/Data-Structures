/*
Consider the following dataset click here. The dataset consists of a key param-
eter - NHS No., and three value parameters, first name, email and gender,
respectively.
Construct a dictionary with the following hash table size m = {10, 19, 40, 61}.
Prepare a hash table for this dataset for various values of hash table size m using
universal hashing. Collision that occurred during hashing should be addressed
by chaining method. Each node in the linked list should be represented via
struct data type which consists of NHS No. as key parameter; first name,
email and gender as three value parameters; and pointer to the next node.
Output a histogram corresponding to each size of the hash table. The
histogram summarises the number of nodes in the linked list corresponding to
each row of the hash table. You can represent the histogram with a graph in
the X − Y axis, wherein a point (xi

, yi), the xi corresponds to the row in the
hash table, and yi corresponds to the number of nodes in the linked list.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TABLE_SIZE 100
#define MAX_LINE_LENGTH 1024

// Struct to store user information
struct node
{
    long long nhsNo;
    char firstName[50];
    char email[50];
    char gender[50];
    struct node* next;
};

// Function to create a new user info node
struct node* createNode(long long nhsNo, const char* firstName, const char* email, const char* gender) 
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->nhsNo = nhsNo;
    strcpy(newNode->firstName, firstName);
    strcpy(newNode->email, email);
    strcpy(newNode->gender, gender);
    newNode->next = NULL;
    return newNode;
}

int HashedIndex(long long nhsNo, int tablesize)
{
    long long a = rand();
    return ((a*nhsNo)%tablesize);
}

// Function to insert a node into the hash table
void insertNode(struct node* hashTable[], int tableSize, long long nhsNo, const char* firstName, const char* email, const char* gender) 
{
    int index = HashedIndex(nhsNo, tableSize);

    // Create a new node
    struct node* newNode = createNode(nhsNo, firstName, email, gender);

    // Insert the new node into the linked list at the specified index
    if (hashTable[index] == NULL) 
    {
        hashTable[index] = newNode;
    } 
    else 
    {
        struct node* current = hashTable[index];
        while (current->next != NULL) 
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to print the hash table histogram
void printHistogram(struct node* hashTable[], int tableSize) 
{
    printf("Histogram:\n");
    for (int i = 0; i < tableSize; i++) 
    {
        int count = 0;
        struct node* current = hashTable[i];
        while (current != NULL) {
            count++;
            current = current->next;
        }
        printf("%d -> %d\n", i, count);
    }
}

int main() 
{
    int sizes[] = {10, 19, 40, 61};
    int m;
    for(int i=0; i<4; i++)
    {
        m = sizes[i];
        
        struct node* hashTable[MAX_TABLE_SIZE] = {NULL};

        printf("Generating for m = %d\n", m);

        // Loading CSV file
        FILE* file = fopen("Data.csv", "r");
        if (file == NULL) 
        {
            fprintf(stderr, "Error opening CSV file.\n");
            return 1;
        }

        char line[MAX_LINE_LENGTH];
        fgets(line, sizeof(line), file);

        while (fgets(line, sizeof(line), file)) 
        {
            long long nhsNo;
            char firstName[50];
            char email[50];
            char gender[50];

            sscanf(line, "%*d,%d,%49[^,],%49[^,],%c", &nhsNo, firstName, email, gender);
            insertNode(hashTable, m, nhsNo, firstName, email, gender);
        }

        fclose(file);

        printHistogram(hashTable, m);

        // Free allocated memory
        for (int i = 0; i < m; i++) 
        {
            struct node* current = hashTable[i];
            while (current != NULL) 
            {
                struct node* temp = current;
                current = current->next;
                free(temp);
            }
        }
        printf("\n");
    }
    
    return 0;
}
