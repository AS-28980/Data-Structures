/*
Suppose G = (V, E) an undirected weighted graph is given as input.
Compute the MST of this graph using Prim’s algorithm. You need
to output the list of edges that comprises MST.
*/
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Function to find the vertex with the minimum key value
int findMinKey(int key[], bool isInMST[], int vertices) 
{
    int min = INT_MAX, minIndex;

    for (int vertex = 0; vertex < vertices; vertex++) 
    {
        if (!isInMST[vertex] && key[vertex] < min) 
        {
            min = key[vertex];
            minIndex = vertex;
        }
    }

    return minIndex;
}

// Function to print the Minimum Spanning Tree
void printMST(int parent[], int graph[MAX_VERTICES][MAX_VERTICES], int vertices) 
{
    printf("\n");
    for (int vertex = 1; vertex < vertices; vertex++)
        printf("%d %d %d \n", parent[vertex], vertex, graph[vertex][parent[vertex]]);
}

// Function to find the Minimum Spanning Tree using Prim's algorithm
void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int vertices) 
{
    int *parent = (int *)malloc(vertices * sizeof(int));   // To store the parent of each vertex in MST
    int *key = (int *)malloc(vertices * sizeof(int));      // To store the key (weight) of each vertex
    bool *isInMST = (bool *)malloc(vertices * sizeof(bool)); // To track whether a vertex is included in MST or not

    // Check for memory allocation errors
    if (parent == NULL || key == NULL || isInMST == NULL) 
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Initialization
    for (int i = 0; i < vertices; i++) 
    {
        key[i] = INT_MAX;
        isInMST[i] = false;
    }

    key[0] = 0;
    parent[0] = -1; // First vertex is the root of MST

    // Construct MST
    for (int count = 0; count < vertices - 1; count++) 
    {
        int u = findMinKey(key, isInMST, vertices); // Find the vertex with the minimum key value

        isInMST[u] = true;

        // Update key and parent values of the adjacent vertices of u
        for (int v = 0; v < vertices; v++) 
        {
            if (graph[u][v] && !isInMST[v] && graph[u][v] < key[v]) 
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the MST
    printMST(parent, graph, vertices);

    // Calculate and print the weight of MST
    int totalWeight = 0;
    for (int i = 1; i < vertices; i++)
        totalWeight += graph[i][parent[i]];

    printf("%d\n", totalWeight);

    // Free allocated memory
    free(parent);
    free(key);
    free(isInMST);
}

int main() 
{
    int v, e;
    while(1)
    {
        scanf("%d %d", &v, &e);

        int graph[MAX_VERTICES][MAX_VERTICES] = {0};

        // Input the edges of the graph
        for (int i = 0; i < e; i++) 
        {
            int source, destination, weight;
            scanf("%d %d %d", &source, &destination, &weight);
            graph[source][destination] = graph[destination][source] = weight;
        }

        // Find and print the Minimum Spanning Tree
        primMST(graph, v);
        printf("\n");
    }

    return 0;
}
