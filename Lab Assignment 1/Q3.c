/*
Write a C program to implement two stacks in one array A[1, 2, . . . , n] so
that neither stack overflows unless the total number of elements in both
stacks together is n. The PUSH and POP operations should run in O(1)
time.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 // Maximum size of the array

typedef struct 
{
    int arr[MAX_SIZE];
    int top1; // Top index of Stack 1
    int top2; // Top index of Stack 2
} TwoStacks;

// Initialize two stacks in an array
void initTwoStacks(TwoStacks *ts, int n) 
{
    ts->top1 = -1;
    ts->top2 = n;
}

// Push operation for Stack 1
void pushStack1(TwoStacks *ts, int data) 
{
    if (ts->top1 + 1 < ts->top2) 
    {
        ts->top1++;
        ts->arr[ts->top1] = data;
    } 
    else 
    {
        printf("Stack overflow!\n");
    }
}

// Push operation for Stack 2
void pushStack2(TwoStacks *ts, int data) 
{
    if (ts->top2 - 1 > ts->top1) 
    {
        ts->top2--;
        ts->arr[ts->top2] = data;
    } 
    else 
    {
        printf("Stack overflow!\n");
    }
}

// Pop operation for Stack 1
int popStack1(TwoStacks *ts) 
{
    if (ts->top1 >= 0) 
    {
        int data = ts->arr[ts->top1];
        ts->top1--;
        return data;
    } 
    else 
    {
        printf("Stack 1 underflow!\n");
        return -1;
    }
}

// Pop operation for Stack 2
int popStack2(TwoStacks *ts) 
{
    if (ts->top2 < MAX_SIZE) 
    {
        int data = ts->arr[ts->top2];
        ts->top2++;
        return data;
    } 
    else 
    {
        printf("Stack 2 underflow!\n");
        return -1;
    }
}

int main() 
{
    int n, choice, data;
    
    printf("Enter the value of n: ");
    scanf("%d", &n);
    
    TwoStacks ts;
    initTwoStacks(&ts, n);

    while (1) 
    {
        printf("\n1. Push to Stack 1\n");
        printf("2. Push to Stack 2\n");
        printf("3. Pop from Stack 1\n");
        printf("4. Pop from Stack 2\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Enter element to push to Stack 1: ");
                scanf("%d", &data);
                pushStack1(&ts, data);
                break;
            case 2:
                printf("Enter element to push to Stack 2: ");
                scanf("%d", &data);
                pushStack2(&ts, data);
                break;
            case 3:
                printf("Popped from Stack 1: %d\n", popStack1(&ts));
                break;
            case 4:
                printf("Popped from Stack 2: %d\n", popStack2(&ts));
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
