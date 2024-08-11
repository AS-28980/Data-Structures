/*
Write a C program to implement a queue using two stacks; that is, you
are supposed to use the functionality of Push and Pop, and mimic the
functionality of enqueue and dequeue operation. Analyze the running
time of the queue operations
*/
#include <stdio.h>
#include <stdlib.h>


struct node
{
    int data;
    struct node *next;
};


void push(struct node** top, int data)
{
    struct node* temp = (struct node*) malloc(sizeof(struct node));
        if (temp == NULL) 
        {
            printf("Stack overflow \n");
            return;
        }
    temp->data = data;
    temp->next = (*top);
    (*top) = temp;
}

int pop(struct node** top)
{
    int popped;
    struct node *t;
    if (*top == NULL) 
    {
        printf("Stack underflow \n");
        return;
    }
    else 
    {
        t = *top;
        popped = t->data;
        *top = t->next;
        return popped;
    }
}


struct queue
{
    struct node *stack1;
    struct node *stack2;
};


void enqueue(struct queue *q, int x)
{
    push(&q->stack1, x);
}

void dequeue(struct queue *q)
{
    int x;
    if (q->stack1 == NULL && q->stack2 == NULL) 
    {
        printf("Queue is empty\n");
        return;
    }
    if (q->stack2 == NULL) 
    {
        while (q->stack1 != NULL) 
        {
            x = pop(&q->stack1);
            push(&q->stack2, x);
        }
    }
    x = pop(&q->stack2);
    printf("%d\n", x);
}


void display(struct node *top1,struct node *top2)
{
    printf("Current status of queue: ");
    while (top1 != NULL) 
    {
        printf("%d  ", top1->data);
        top1 = top1->next;
    }
    while (top2 != NULL) 
    {
        printf("%d  ", top2->data);
        top2 = top2->next;
    }
    printf("\n\n");
}

int main()
{
    struct queue *q = (struct queue*)malloc(sizeof(struct queue));
    int c = 0, a;
    q->stack1 = NULL;
    q->stack2 = NULL;
    while (1) 
    {
        printf("Enter your choice\n1.Add to queue\n2.Remove from queue\n3.Display\n4.Exit\n");
        scanf("%d", &c);
        switch(c) 
        {
            case 1 : printf("Enter the element to be added to queue\n");
                     scanf("%d", &a);
                     enqueue(q, a);
                     break;
            case 2 : dequeue(q);
                     break;
            case 3 : display(q->stack1, q->stack2);
                     break;
            case 4 : exit(1);
                     break;
            default : printf("invalid\n");
                      break;
        }
    }
}