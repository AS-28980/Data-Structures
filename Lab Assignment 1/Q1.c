/*
Write a C code that takes a postfix expression as input and outputs the
corresponding result using the stack data structure. For example: if the
input is ‘‘2 3 +’’ the output should be ‘‘5’’.
You can assume that the user inputs the postfix expression in the correct
format.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack
{
    int top;
    int size;
    int *arr;
};

struct Stack *create(int size)
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->size = size;
    stack->top = -1;
    stack->arr = (int *)malloc(stack->size * sizeof(int));
    return stack;
}

int isFull(struct Stack *stack)
{
    return stack->top == stack->size - 1;
}

int isEmpty(struct Stack *stack)
{
    return stack->top == -1;
}

void push(struct Stack *stack, int item)
{
    if (isFull(stack))
    {
        printf("Stack is full\n");
        return;
    }
    stack->top++;
    stack->arr[stack->top] = item;
}

int pop(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE); // Exit the program in case of underflow
    }
    return stack->arr[stack->top--];
}

int main()
{
    struct Stack *stack = create(100); // Adjust the size as needed
    printf("Enter elements in postfix form: ");
    char str[100];
    fgets(str, sizeof(str), stdin);

    int len = strlen(str);
    int a = 0;
    for (int i = 0; i < len; i++)
    {
        char c = str[i];
        if (c >= '0' && c <= '9')
        {
            a = a * 10 + (c - '0');
        }
        else if (c == ' ')
        {
            push(stack, a);
            a = 0;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
        {
            int b = pop(stack);
            int a = pop(stack);
            if (c == '+')
            {
                push(stack, a + b);
            }
            else if (c == '-')
            {
                push(stack, a - b);
            }
            else if (c == '*')
            {
                push(stack, a * b);
            }
            else if (c == '/')
            {
                if (b == 0)
                {
                    printf("Error: Division by zero\n");
                    exit(EXIT_FAILURE);
                }
                push(stack, a / b);
            }
            else if (c == '%')
            {
                push(stack, a % b);
            }
            i++;
        }
    }

    printf("Result: %d\n", stack->arr[stack->top]);

    free(stack->arr);
    free(stack);
    return 0;
}
