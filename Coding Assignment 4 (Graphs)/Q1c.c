/*
Given a graph as input, write an algorithm to check whether it is
bi-partite. Recall that a graph is called bi-partite if its vertices can
be partitioned into two sets such that there are no edges within the
same partition and edges exist only across the partition.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_V 100

bool isBipartite(int G[MAX_V][MAX_V], int V)
{
    int src = 0;
    int *colorArr = (int *)malloc(V * sizeof(int));

    if (colorArr == NULL)
    {
        fprintf(stderr, "Memory allocation error for colorArr\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < V; ++i)
        colorArr[i] = -1;

    colorArr[src] = 1;

    int *queue = (int *)malloc(V * sizeof(int));
    if (queue == NULL)
    {
        fprintf(stderr, "Memory allocation error for queue\n");
        free(colorArr);
        exit(EXIT_FAILURE);
    }

    int front = -1, rear = -1;
    queue[++rear] = src;

    while (front != rear)
    {
        int u = queue[++front];
        if (G[u][u] == 1)
        {
            free(colorArr);
            free(queue);
            return false;
        }
        for (int v = 0; v < V; ++v)
        {
            if (G[u][v] && colorArr[v] == -1)
            {
                colorArr[v] = 1 - colorArr[u];
                queue[++rear] = v;
            }
            else if (G[u][v] && colorArr[v] == colorArr[u])
            {
                free(colorArr);
                free(queue);
                return false;
            }
        }
    }

    free(colorArr);
    free(queue);
    return true;
}

int main()
{
    int G[MAX_V][MAX_V];
    int V, E;
    while(1)
    {
        if (scanf("%d %d", &V, &E) != 2 || V <= 0 || E < 0 || E > V * (V - 1) / 2)
        {
            fprintf(stderr, "Invalid input for V and E\n");
            return EXIT_FAILURE;
        }

        int a1, a2;
        for (int i = 0; i < E; i++)
        {
            if (scanf("%d %d", &a1, &a2) != 2 || a1 < 0 || a1 >= V || a2 < 0 || a2 >= V)
            {
                fprintf(stderr, "Invalid input for edge\n");
                return EXIT_FAILURE;
            }
            G[a1][a2] = G[a2][a1] = 1;
        }

        isBipartite(G, V) ? printf("Yes\n\n") : printf("No\n\n");
    }
    return 0;
}
