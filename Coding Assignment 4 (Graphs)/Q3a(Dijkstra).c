/*
Suppose G = (V, E) - a directed weighted graph with non-negative
edge weights and a vertex s ∈ V , are given as input. Implement
Dijkstra’s algorithm for computing the shortest path of ∀v ∈ V /s
from the vertex s. ∀v ∈ V /s, you need to output both - the length
of the shortest path of v from s, and the list of vertices in the path.
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define infi INT_MAX

struct Edge 
{
    int destination;
    int weight;
    struct Edge* next;
};

struct Node 
{
    int vertexNumber;
    struct Edge* children;
};

void add_child(struct Node* node, int destination, int weight) 
{
    struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge));
    if (newEdge == NULL) 
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    newEdge->destination = destination;
    newEdge->weight = weight;
    newEdge->next = node->children;
    node->children = newEdge;
}

int* dijkstraDist(struct Node* graph, int v, int s, int* path) 
{
    int* dist = (int*)malloc(v * sizeof(int));
    int* visited = (int*)malloc(v * sizeof(int));
    int* parent = (int*)malloc(v * sizeof(int));

    if (dist == NULL || visited == NULL || parent == NULL) 
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < v; ++i) 
    {
        visited[i] = 0;
        path[i] = -1;
        dist[i] = infi;
    }

    dist[s] = 0;
    parent[s] = -1;

    for (int count = 0; count < v - 1; ++count) 
    {
        int minDist = infi;
        int current = -1;
        for (int i = 0; i < v; ++i) 
        {
            if (!visited[i] && dist[i] < minDist) 
            {
                minDist = dist[i];
                current = i;
            }
        }

        if (current == -1) 
        {
            fprintf(stderr, "Error: Unable to find a valid path.\n");
            exit(EXIT_FAILURE);
        }

        visited[current] = 1;

        struct Edge* edge = graph[current].children;
        while (edge != NULL) {
            int dest = edge->destination;
            if (!visited[dest]) 
            {
                int alt = dist[current] + edge->weight;
                if (alt < dist[dest]) 
                {
                    dist[dest] = alt;
                    parent[dest] = current;
                }
            }
            edge = edge->next;
        }
    }

    for (int i = 0; i < v; ++i)
        path[i] = parent[i];

    free(visited);
    free(parent);

    return dist;
}

void printPath(int* path, int i, int s, int destination) 
{
    if (i != s) 
    {
        if (path[i] == -1) 
        {
            printf("Path not found!!");
            return;
        }
        printPath(path, path[i], s, destination);
        printf("%d ", path[i]);
    }
    if (i == destination) 
        printf("%d ", destination);
}

int main() 
{
    int v, e, s;
    while(1)
    {
        if (scanf("%d %d %d", &v, &e, &s) != 3 || v <= 0 || e < 0 || s < 0 || s >= v) 
        {
            fprintf(stderr, "Error: Invalid input format or values.\n");
            return EXIT_FAILURE;
        }

        struct Node* graph = (struct Node*)malloc(v * sizeof(struct Node));
        if (graph == NULL) 
        {
            perror("Memory allocation failed");
            return EXIT_FAILURE;
        }

        for (int i = 0; i < v; ++i) 
        {
            graph[i].vertexNumber = i;
            graph[i].children = NULL;
        }

        for (int i = 0; i < e; ++i) 
        {
            int a, b, w;
            if (scanf("%d %d %d", &a, &b, &w) != 3 || a < 0 || b < 0 || a >= v || b >= v) 
            {
                fprintf(stderr, "Error: Invalid input format or values.\n");
                free(graph);
                return EXIT_FAILURE;
            }
            add_child(&graph[a], b, w);
        }

        int* path = (int*)malloc(v * sizeof(int));

        int* dist = dijkstraDist(graph, v, s, path);

        printf("\n");
        for (int i = 0; i < v; ++i) 
        {
            if (i != s) 
            {
                printPath(path, i, s, i);
                if (dist[i] == infi)
                    printf("No path");
                else
                    printf("%d", dist[i]);
                printf("\n");
            }
        }

        free(path);
        free(dist);

        // Freeing memory for the graph
        for (int i = 0; i < v; ++i) 
        {
            struct Edge* edge = graph[i].children;
            while (edge != NULL) 
            {
                struct Edge* nextEdge = edge->next;
                free(edge);
                edge = nextEdge;
            }
        }
        printf("\n");
        free(graph);
    }
    
    return 0;
}
