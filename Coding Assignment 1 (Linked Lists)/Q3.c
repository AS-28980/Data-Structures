/*
Write a program that takes an infix arithmetic expression as input and
outputs the corresponding postfix expression. You can assume that the
infix statement is given in the correct format.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxLen 100

struct Stack
{
    int size;
    int top;
    char *array;
};

typedef struct Stack Stack;

Stack *initialize(int size)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->size = size;
    stack->top = -1;
    stack->array = (char *)malloc(size * sizeof(char));
    return stack;
}

int isEmpty(Stack *stack)
{
    return (stack->top == -1);
}

int isFull(Stack *stack)
{
    return (stack->top == stack->size - 1);
}

void push(Stack *stack, char data)
{
    stack->top++;
    stack->array[stack->top] = data;
}

char pop(Stack *stack)
{
    return stack->array[stack->top--];
}

char topEle(Stack *stack)
{
    return stack->array[stack->top];
}

int operatorPrecedence(char c)
{
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/' || c == '%')
        return 2;
    else if(c == '^')
        return 3;
    return 0;
}

int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c=='^');
}

int main()
{
    printf("Enter an infix expression:\n");
    char infix[MaxLen];
    char postfix[MaxLen];
    fgets(infix, MaxLen, stdin);
    Stack *stack = initialize(MaxLen);
    int i = 0, j = 0;

    while (infix[i] != '\n')
    {
        if (infix[i] == ' ')
        {
            i++;
            continue;
        }
        if (isOperator(infix[i]) || infix[i] == '(' || infix[i] == ')')
        {
            char op = infix[i];
            if (op == '(')
            {
                push(stack, op);
            }
            else if (op == ')')
            {
                while (!isEmpty(stack) && topEle(stack) != '(')
                {
                    postfix[j++] = pop(stack);
                }
                pop(stack); // Pop '('
            }
            else
            {
                while (!isEmpty(stack) && topEle(stack) != '(' &&
                       operatorPrecedence(op) <= operatorPrecedence(topEle(stack)))
                {
                    postfix[j++] = pop(stack);
                }
                push(stack, op);
            }
            i++;
        }
        else
        {
            postfix[j++] = infix[i];
            i++;
        }
    }

    while (!isEmpty(stack))
    {
        postfix[j++] = pop(stack);
    }
    postfix[j] = '\0';

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
