/*
Given a singly linked list along with its head pointer, return true if it
is a palindrome or false otherwise. Your algorithm’s time and space
complexity should be O(n) and O(1), respectively.
*/
#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
};

typedef struct node node;

node* createList(int n)
{
    printf("Enter values one by one:\n");
    node *head = NULL, *temp = NULL, *first = NULL;
    
    for (int i = 0; i < n; i++)
    {
        temp = (node*)malloc(sizeof(node));
        scanf("%d", &temp->data);
        
        if (first == NULL)
        {
            first = temp;
            head = temp;
        }
        else
        {
            head->next = temp;
            head = temp;
        }
        
        temp->next = NULL;
    }
    
    return first;
}

node* reverse(node* head)
{
    node *current = head, *next = NULL, *prev = NULL;
    while(current!=NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    return head;
}

void printList(node* head)
{
    while (head->next != NULL)
    {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("%d\n", head->data);
}

int check(node* head)
{
    node* temp;
    int size=0;
    temp=head;
    while(temp!=NULL)
    {
        size++;
        temp = temp->next;
    }
    temp = head;
    if(size%2 == 0)
    {
        for(int i=1; i<size/2; i++)
        {
            temp = temp->next;
        }
    }
    else
    {
        for(int i=1; i<(size+1)/2; i++)
        {
            temp = temp->next;
        }
    }
    temp->next = reverse(temp->next);
    temp = temp->next;
    while(temp!=NULL)
    {
        if(head->data != temp->data)
            return 0;
        head = head->next;
        temp = temp->next;
    }
    return 1;
}

int main()
{
    printf("Enter size of the linked list: ");
    int n;
    scanf("%d", &n);
    node *head = createList(n);
    int res = check(head);
    if(res == 1)
        printf("true");
    else
        printf("false");
}