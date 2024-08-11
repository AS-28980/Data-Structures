/*
Given a singly linked list along with its head pointer, the problem is to
group all the nodes with odd indices, followed by the nodes with even
indices, and return the reordered list. The relative order inside the even
and odd groups should remain in the input. The following figure illustrates
the scenario:
Your algorithm’s time and space complexity should be O(n) and O(1),
respectively.
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

void printList(node* head)
{
    while (head->next != NULL)
    {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("%d\n", head->data);
}

node* rearrange(node* head)
{
    if (head == NULL || head->next == NULL) 
    {
        return head;
    }

    node* oddHead = head;
    node* evenHead = head->next;
    node* oddCurrent = oddHead;
    node* evenCurrent = evenHead;

    /*The pointers keep making and breaking links to split the given linked list in two,
      one with all the odd indices and one with all the even indices*/
    while (evenCurrent != NULL && evenCurrent->next != NULL)
    {
        oddCurrent->next = evenCurrent->next;
        oddCurrent = oddCurrent->next;
        evenCurrent->next = oddCurrent->next;
        evenCurrent = evenCurrent->next;
    }

    oddCurrent->next = evenHead; // Connect the end of odd list to the beginning of even list

    return oddHead;
}

int main()
{
    printf("Enter size of the linked list: ");
    int n;
    scanf("%d", &n);
    node *head = createList(n);
    
    printf("Original Linked List: ");
    printList(head);

    node *newHead = rearrange(head);
    printf("Rearranged Linked List: ");
    printList(newHead);

    return 0;
}
