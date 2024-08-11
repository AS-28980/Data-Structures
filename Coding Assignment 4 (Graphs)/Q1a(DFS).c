/*
Suppose G = (V, E) - an undirected graph, and a vertex s ∈ V are
given as input. Given the non-recursive implementation of the DFS
traversal algorithm. ∀v ∈ V , you need to output both - the length of
the path from s, and the list of vertices in the path.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Structure to represent a node in the adjacency list
struct Node 
{
    int vertex;
    struct Node* next;
};
typedef struct Node Node;

// Structure to represent the adjacency list for each vertex
struct Graph 
{
    struct Node* adjList[MAX_VERTICES];
};
typedef struct Graph Graph;

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->vertex = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Add an edge from dest to src (since it's an undirected graph)
    newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->vertex = src;
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Function to perform DFS and find a path from source to destination
int DFS(Graph* graph, int current, int destination, int visited[], int path[], int pathIndex) 
{
    // Mark the current node as visited
    visited[current] = 1;
    path[pathIndex] = current;
    pathIndex++;

    // If the current node is the destination, print the path
    if (current == destination) 
    {
        for (int i = 0; i < pathIndex; ++i)
            printf("%d ", path[i]);
        printf("%d", pathIndex - 1);
        return 1;
    }

    Node* temp = graph->adjList[current];
    while (temp != NULL) 
    {
        if (!visited[temp->vertex]) 
        {
            if (DFS(graph, temp->vertex, destination, visited, path, pathIndex))
                return 1; // Path found, stop further exploration
        }
        temp = temp->next;
    }

    return 0; // Path not found
}

int main() 
{
    int v, e, s, a1, a2;

    while (1) 
    {
        if (scanf("%d %d %d", &v, &e, &s) != 3) 
        {
            fprintf(stderr, "Invalid input\n");
            exit(EXIT_FAILURE);
        }

        Graph* graph = (Graph*)malloc(sizeof(Graph));
        if (graph == NULL) 
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < MAX_VERTICES; ++i)
            graph->adjList[i] = NULL;

        for (int i = 0; i < e; ++i) 
        {
            if (scanf("%d %d", &a1, &a2) != 2) 
            {
                fprintf(stderr, "Invalid input\n");
                exit(EXIT_FAILURE);
            }
            addEdge(graph, a1, a2);
        }

        for (int i = 0; i < v; i++) 
        {
            if (i == s)
                continue;
            int visited[MAX_VERTICES] = {0};
            int path[MAX_VERTICES];
            int pathIndex = 0;

            printf("\n");
            if (!DFS(graph, s, i, visited, path, pathIndex))
                printf("No path from %d to %d", s, i);
        }
        free(graph); // Free allocated memory
        printf("\n\n");
    }
    return 0;
}
