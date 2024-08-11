/*
Write a C program that takes a queue (over integers) and an integer k as
input, and reverse the first k element of the queue. You can take an array
implementation of a queue that supports enqueue and dequeue operation.
*/
#include <stdio.h>
#define MAX_SIZE 100

struct Queue 
{
    int front, rear, size;
    int arr[MAX_SIZE];
};

void initQueue(struct Queue *q) 
{
    q->front = -1;
    q->rear = -1;
    q->size = 0;
}

int isEmpty(struct Queue *q) 
{
    return q->size == 0;
}

int isFull(struct Queue *q) 
{
    return q->size == MAX_SIZE;
}

void enqueue(struct Queue *q, int data) 
{
    if (isFull(q)) 
    {
        printf("Queue is full\n");
        return;
    }
    if (q->front == -1) 
    {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->arr[q->rear] = data;
    q->size++;
}

int dequeue(struct Queue *q) 
{
    if (isEmpty(q)) 
    {
        printf("Queue is empty\n");
        return -1;
    }
    int data = q->arr[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->size--;
    if (q->size == 0) 
    {
        q->front = -1;
        q->rear = -1;
    }
    return data;
}

void reverseFirstK(struct Queue *q, int k) 
{
    if (k <= 0 || k > q->size) 
    {
        printf("Invalid value of k\n");
        return;
    }

    int temp[k];
    for (int i = 0; i < k; i++) 
    {
        temp[i] = dequeue(q);
    }

    for (int i = k - 1; i >= 0; i--) 
    {
        enqueue(q, temp[i]);
    }

    for (int i = 0; i < q->size - k; i++) 
    {
        enqueue(q, dequeue(q));
    }
}

int main() 
{
    struct Queue q;
    initQueue(&q);

    int n, num, k;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &num);
        enqueue(&q, num);
    }

    printf("Enter the value of k: ");
    scanf("%d", &k);

    reverseFirstK(&q, k);

    printf("Queue after reversing first %d elements: ", k);
    while (!isEmpty(&q)) 
    {
        int data = dequeue(&q);
        printf("%d ", data);
    }
    printf("\n");

    return 0;
}

