/*
The dynamic-set operation SET UNION takes two disjoint sets S1 and S2
as input, and it returns a set S = S1 ∪ S2 consisting of all the elements
of S1 and S2. The operation usually destroys the sets S1 and S2. Using
a suitable list data structure, show how to support SET UNION in O(1)

In this problem for simplicity you can assume that your
set is the set of integers. A pair of sets S1 and S2 are said to be disjoint
if they don’t have any element in common. You need to check which data
structure is suitable for the purpose, and for the problem you need to use
the functionality of that data structure only. For e.g. if you plan to use
stack data structure for this problem, then you can assess its elements via
Push and Pop methods only. You are not allowed to use a doubly-linked list. 
If you are using a singly linked list, you have access to only the head
pointer of the list.
*/
#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node* next;
};
typedef struct node node;
node *S1, *S2;

node* create()
{
    node* head = (node*)malloc(sizeof(node));
    node* first = head;
    printf("Enter first element: ");
    scanf("%d", &head->data);
    node* temp;
    while(1)
    {
        printf("Do you want to add more elements?(1 for yes, 0 for no): ");
        int choice;
        scanf("%d", &choice);
        if(choice)
        {
            temp = (node*)malloc(sizeof(node));
            printf("Enter element: ");
            scanf("%d", &temp->data);
            temp->next = NULL;
            head->next = temp;
            head = temp;
        }
        else
            break;
    }
    printf("\n");
    head->next = first;
    return first;
}

void setUnion(node** head1, node** head2)
{
    node* temp;
    temp = (*head2)->next;
    (*head2)->next = (*head1)->next;
    (*head1)->next = temp;
}

void printList(node* head)
{
    node* first = head;
    while(head->next != first)
    {
        printf("%d, ", head->data);
        head = head->next;
    }
    printf("%d\n\n", head->data);
}

int main()
{
    printf("Creating set 1:-\n");
    S1 = create();
    printf("Creating set 2:-\n");
    S2 = create();
    printf("Elements of set 1: ");
    printList(S1);
    printf("Elements of set 1: ");
    printList(S2);
    setUnion(&S1, &S2);
    printf("Elements of union: ");
    printList(S1);
}