#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INITIAL_CAPACITY 100000
#define GROWTH_FACTOR 2

// Define a structure for key-value pairs
typedef struct node {
    int key;
    int value;
} node;

// Create a hash table structure
typedef struct HashTable {
    int size;
 node** table;
} HashTable;

// Create a simple hash function
int hash(int key, int size) {
    return key % size;
}

// Initialize a hash table
HashTable* initializeHashTable(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->table = (node**)malloc(sizeof (node*) * size);
    for (int i = 0; i < size; i++) {
        table->table[i] = NULL;
    }
    return table;
}

// Insert a key-value pair into the hash table
void insert(HashTable* table, int key, int value) {
    int index = hash(key, table->size);

    if (table->table[index] == NULL) {
        table->table[index] =  (node*)malloc(sizeof (node));
        table->table[index]->key = key;
        table->table[index]->value = value;
    }
}

// Retrieve a value from the hash table based on the key
int retrieve(HashTable* table, int key) {
    int index = hash(key, table->size);
    if (table->table[index] == NULL) {
        return -1;  // Key not found
    }
    return table->table[index]->value;
}

int main() {
    srand(time(NULL));

    const char* datasetFileName = "T10I4D100K.txt"; // Replace with the actual file path

    FILE* datasetFile = fopen(datasetFileName, "r");
    if (datasetFile == NULL) {
        perror("Failed to open the dataset file");
        return 1;
    }

    int* dataset = NULL;
    int data;
    int dataSize = 0;
    int capacity = INITIAL_CAPACITY;

    dataset = (int*)malloc(capacity * sizeof(int));
    if (dataset == NULL) {
        perror("Failed to allocate memory for the dataset");
        return 1;
    }

    while (fscanf(datasetFile, "%d", &data) == 1) {
        if (dataSize >= capacity) {
            // Resize the dataset array dynamically when needed
            capacity *= GROWTH_FACTOR;
            dataset = (int*)realloc(dataset, capacity * sizeof(int));
            if (dataset == NULL) {
                perror("Failed to reallocate memory for the dataset");
                return 1;
            }
        }

        dataset[dataSize] = data;
        dataSize++;
    }

    fclose(datasetFile);

    // Define the subset size (5% of the dataset)
    int subset_size = dataSize * 0.05;  // Calculate the subset size

    // Create a test dataset from the first 5% of elements
    int* test_data = (int*)malloc(subset_size * sizeof(int));
    for (int i = 0; i < subset_size; i++) {
        test_data[i] = dataset[i];
    }

    // Initialize a hash table
    HashTable* table = initializeHashTable(subset_size);

    // Insert key-value pairs into the hash table
    for (int i = 0; i < subset_size; i++) {
        insert(table, test_data[i], test_data[i]);
    }

    // Evaluate the perfect hash table on the test dataset
    int true_positive = 0;
    int true_negative = 0;
    int false_positive = 0;
    int false_negative = 0;

    for (int i = 0; i < subset_size; i++) {
        int key = test_data[i];
        int predicted_value = retrieve(table, key);
        if (key == predicted_value) {
            if (key == dataset[i]) {
                true_positive++;
            } else {
                false_positive++;
            }
        } else {
            if (key == dataset[i]) {
                false_negative++;
            } else {
                true_negative++;
            }
        }
    }

    // Calculate and print the confusion matrix
    printf("True Positive: %d\n", true_positive);
    printf("True Negative: %d\n", true_negative);
    printf("False Positive: %d\n", false_positive);
    printf("False Negative: %d\n", false_negative);

    // Free dynamically allocated memory
    free(test_data);
    for (int i = 0; i < subset_size; i++) {
        free(table->table[i]);
    }
    free(table->table);
    free(table);

    return 0;
}
