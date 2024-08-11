/*
Suppose G = (V, E) - an undirected graph, and a vertex s ∈ V are
given as input. Implement the BFS traversal algorithm. ∀v ∈ V , you
need to output both - the length of the path from s, and the list of
vertices in the path.
*/
#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MAX_VERTICES 1000

// Node structure for adjacency list
struct Node 
{
    int dest;
    struct Node* next;
};
typedef struct Node Node;

// Vertex structure
struct Vertex 
{
    int color;
    int distance;
    int parent;
    Node* head; // Head of the adjacency list
};
typedef struct Vertex Vertex;

// Queue structure
struct Queue 
{
    int front, rear;
    int capacity;
    int* array;
};
typedef struct Queue Queue;

struct Stack 
{
    int top;
    int capacity;
    int* array;
};
typedef struct Stack Stack;

Queue* createQueue(int capacity) 
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) 
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    if (queue->array == NULL) 
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    return queue;
}

Stack* createStack(int capacity) 
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) 
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    if (stack->array == NULL) 
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    return stack;
}

int isEmpty(Queue* queue) 
{
    return queue->front == -1;
}

int isStackEmpty(Stack* stack) 
{
    return stack->top == -1;
}

void enqueue(Queue* queue, int item) 
{
    if (queue->rear == queue->capacity - 1) 
    {
        fprintf(stderr, "Queue overflow\n");
        exit(EXIT_FAILURE);
    }
    queue->array[++queue->rear] = item;
    if (queue->front == -1)
        queue->front = 0;
}

int dequeue(Queue* queue) 
{
    if (isEmpty(queue)) 
    {
        fprintf(stderr, "Queue underflow\n");
        exit(EXIT_FAILURE);
    }
    int item = queue->array[queue->front++];
    if (queue->front > queue->rear) 
        queue->front = queue->rear = -1;
    return item;
}

void push(Stack* stack, int item) 
{
    if (stack->top == stack->capacity - 1) 
    {
        fprintf(stderr, "Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->array[++stack->top] = item;
}

int pop(Stack* stack) 
{
    if (isStackEmpty(stack)) 
    {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->array[stack->top--];
}

void addEdge(Vertex* vertices, int src, int dest) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) 
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    newNode->dest = dest;
    newNode->next = vertices[src].head;
    vertices[src].head = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) 
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    newNode->dest = src;
    newNode->next = vertices[dest].head;
    vertices[dest].head = newNode;
}

void freeMemory(Vertex* vertices, int N) 
{
    for (int i = 0; i < N; ++i) 
    {
        Node* current = vertices[i].head;
        while (current != NULL) 
        {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(vertices);
}

void BFS(Vertex* vertices, int verticesCount, int source) 
{
    Queue* queue = createQueue(verticesCount);

    for (int i = 0; i < verticesCount; ++i) 
    {
        vertices[i].color = WHITE;
        vertices[i].distance = -1;
        vertices[i].parent = -1;
    }

    vertices[source].color = GRAY;
    vertices[source].distance = 0;
    enqueue(queue, source);

    while (!isEmpty(queue)) 
    {
        int u = dequeue(queue);

        Node* neighbor = vertices[u].head;
        while (neighbor != NULL) 
        {
            int v = neighbor->dest;
            if (vertices[v].color == WHITE) 
            {
                vertices[v].color = GRAY;
                vertices[v].distance = vertices[u].distance + 1;
                vertices[v].parent = u;
                enqueue(queue, v);
            }
            neighbor = neighbor->next;
        }

        vertices[u].color = BLACK;
    }

    Stack* stack = createStack(verticesCount);

    for (int i = 1; i < verticesCount; ++i) 
    {
        if (i != source) 
        {
            int current = i;
            while (current != -1) 
            {
                push(stack, current);
                current = vertices[current].parent;
            }

            while (!isStackEmpty(stack))
                printf("%d ", pop(stack));

            printf("%d\n", vertices[i].distance);
        }
    }

    int i = 0;
    if (i != source) 
    {
        int current = i;
        while (current != -1) 
        {
            push(stack, current);
            current = vertices[current].parent;
        }

        while (!isStackEmpty(stack))
            printf("%d ", pop(stack));

        printf("%d\n", vertices[i].distance);
    }

    free(stack->array);
    free(stack);
    free(queue->array);
    free(queue);

    freeMemory(vertices, verticesCount);
}

int main() 
{
    int N, M, s;
    while(1)
    {
        scanf("%d %d %d", &N, &M, &s);

        Vertex* vertices = (Vertex*)malloc(N * sizeof(Vertex));

        if (vertices == NULL) 
        {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < N; ++i)
            vertices[i].head = NULL; // Initialize adjacency list for each vertex

        for (int i = 0; i < M; ++i) 
        {
            int a, b;
            scanf("%d %d", &a, &b);
            addEdge(vertices, a, b);
        }

        printf("\n");

        BFS(vertices, N, s);
        printf("\n");
    }
    return 0;
}
