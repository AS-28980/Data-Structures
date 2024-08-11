/*
Suppose G = (V, E) an undirected weighted graph is given as input.
Compute the MST of this graph using Kruskal’s algorithm. You need
to output the list of edges that comprises MST.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 1000

typedef struct 
{
    int src, dest, weight;
} Edge;

int find(int parent[], int i) 
{
    if (parent[i] != i) 
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

void Union(int parent[], int rank[], int x, int y) 
{
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot]) 
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else 
    {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

int compare(const void* a, const void* b) 
{
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

void kruskalMST(int V, int E, Edge edges[]) 
{
    Edge mst[V];
    int parent[V], rank[V];

    for (int i = 0; i < V; ++i) 
    {
        parent[i] = i;
        rank[i] = 0;
    }

    qsort(edges, E, sizeof(Edge), compare);

    int e = 0, i = 0;
    int totalWeight = 0;

    while (e < V - 1 && i < E) 
    {
        Edge next_edge = edges[i++];

        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        if (x != y) 
        {
            mst[e++] = next_edge;
            totalWeight += next_edge.weight;
            Union(parent, rank, x, y);
        }
    }

    printf("\n");
    for (i = 0; i < e; ++i) 
        printf("%d %d %d\n", mst[i].src, mst[i].dest, mst[i].weight);

    printf("%d\n", totalWeight);
}

int main() 
{
    int V, E;
    while(1)
    {
        scanf("%d %d", &V, &E);

        if (E > MAX_EDGES) 
        {
            printf("Error: Number of edges exceeds the maximum limit.\n");
            return 1;
        }

        Edge *edges = malloc(E * sizeof(Edge));
        if (edges == NULL) 
        {
            printf("Error: Memory allocation failed.\n");
            return 1;
        }

        for (int i = 0; i < E; ++i)
            scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);

        kruskalMST(V, E, edges);
        printf("\n");
        free(edges); // Don't forget to free the allocated memory
    }
    return 0;
}
