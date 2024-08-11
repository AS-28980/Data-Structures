/*
Suppose G = (V, E) - a directed weighted graph (negative edge
weights are also allowed), and a vertex s ∈ V , are given as input.
Write a code to check if the graph has any cycle of negative length.

If it has one, then report it. If the graph doesn’t have any nega-
tive cycle, then compute the shortest path of all the vertices from s.

∀v ∈ V /s, you need to output both - the length of the shortest path
of v from s, and the list of vertices in the path.
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define infi INT_MAX

struct Edge {
    int source;
    int destination;
    int weight;
};
typedef struct Edge Edge;

struct Graph {
    int V;
    int E;
    struct Edge* edges;
};
typedef struct Graph Graph;

void addEdge(Graph* graph, int source, int destination, int weight) {
    graph->edges[graph->E].source = source;
    graph->edges[graph->E].destination = destination;
    graph->edges[graph->E].weight = weight;
    graph->E++;
}

void printPath(int* parent, int v) {
    if (parent[v] == -1) {
        printf("%d ", v);
        return;
    }
    printPath(parent, parent[v]);
    printf("%d ", v);
}

void bellmanFord(Graph* graph, int source) {
    int V = graph->V;
    int E = graph->E;
    int* dist = (int*)malloc(V * sizeof(int));
    int* parent = (int*)malloc(V * sizeof(int));
    int* cycle = (int*)malloc(V * sizeof(int));

    if (dist == NULL || parent == NULL || cycle == NULL) {
        fprintf(stderr, "Memory allocation failed. Exiting.\n");
        exit(EXIT_FAILURE);
    }

    // Initialization
    for (int i = 0; i < V; ++i) {
        dist[i] = infi;
        parent[i] = -1;
    }
    dist[source] = 0;

    // Relaxation step
    int lastRelaxed;
    for (int count = 0; count < V; ++count) {
        lastRelaxed = -1;
        for (int i = 0; i < E; ++i) {
            int u = graph->edges[i].source;
            int v = graph->edges[i].destination;
            int weight = graph->edges[i].weight;

            if (dist[u] != infi && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                lastRelaxed = v;
            }
        }
    }

    // Check for negative cycles
    if (lastRelaxed != -1) {
        int x = lastRelaxed;
        for (int i = 0; i < V; ++i)
            x = parent[x];

        int y = x;
        do {
            cycle[y] = 1;
            y = parent[y];
        } while (y != x);

        int first = x;
        printf("\nYES\nEdges in the cycle: \n");

        do {
            printf("%d %d\n", parent[x], x);
            x = parent[x];
        } while (x != first);

        free(dist);
        free(parent);
        free(cycle);

        // Clear the input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    // Print shortest paths
    for (int i = 0; i < V; ++i) {
        if (i != source) {
            printPath(parent, i);
            printf("%d\n", dist[i]);
        }
    }

    free(dist);
    free(parent);
    free(cycle);
    return;
}

int main() {
    int V, E, source;
    while (1) {
        if (scanf("%d %d %d", &V, &E, &source) != 3) {
            fprintf(stderr, "Invalid input format. Exiting.\n");

            // Clear the input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            
            continue; // Continue to the next iteration on invalid input
        }

        struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
        if (graph == NULL) {
            fprintf(stderr, "Memory allocation failed. Exiting.\n");
            break; // Exit the loop on memory allocation failure
        }

        graph->V = V;
        graph->E = 0;
        graph->edges = (struct Edge*)malloc(E * sizeof(struct Edge));

        if (graph->edges == NULL) {
            fprintf(stderr, "Memory allocation failed. Exiting.\n");
            free(graph);
            break; // Exit the loop on memory allocation failure
        }

        for (int i = 0; i < E; ++i) {
            int u, v, weight;
            if (scanf("%d %d %d", &u, &v, &weight) != 3) {
                fprintf(stderr, "Invalid input format. Exiting.\n");
                free(graph->edges);
                free(graph);

                // Clear the input buffer
                int c;
                while ((c = getchar()) != '\n' && c != EOF);

                continue; // Continue to the next iteration on invalid input
            }
            addEdge(graph, u, v, weight);
        }

        printf("\n");

        bellmanFord(graph, source);

        printf("\n");

        free(graph->edges);
        free(graph);
    }
    return 0;
}
