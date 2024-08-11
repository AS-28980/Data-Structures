/*
Write a C program to implement doubly linked lists using only one pointer
value x->np per item instead of the usual two (x->next and x->prev).
Assume that all pointer values can be interpreted as k-bit integers, and

define x->np to be x->np=x->next XOR x->prev, the k-bit “exclusive-
or” of x->next and x->prev. (The value NIL is represented by 0.) Be

sure to describe what information you need to access the head of the list.
Show how to implement the SEARCH, INSERT, and DELETE operations
on such a list. Also, show how to reverse such a list in O(1) time.
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

struct node
{
    int data;
    struct node* np;
};
typedef struct node node;

struct ListRes
{
    node* head;
    node* tail;
};

typedef struct ListRes res;

node* XOR(node *x, node *y) 
{
    return (node*)((uintptr_t)(x) ^ (uintptr_t)(y)); 
}
////Using uintptr_t lets us temporarily convert the pointers to integers to allow us to XOR them

res* createList()
{
    printf("Enter value to insert in 1st node: ");
    node* head = (node*)malloc(sizeof(node));
    scanf("%d", &head->data);
    int choice = 0;
    head->np = NULL;
    node* first = head;
    node* temp=NULL, *prev=NULL;
    while(1)
    {
        printf("Do you want to continue? Press 1 for yes, 0 for no: ");
        scanf("%d", &choice);
        if(choice == 0)
            break;
        else
        {
            temp = (node*)malloc(sizeof(node));
            head->np =  XOR(prev, temp);
            printf("Enter value: ");
            scanf("%d", &temp->data);
            prev = head;
            head = temp;
            temp = NULL;
        }
    }
    head->np = XOR(prev, NULL);
    printf("\n");
    res *result = (res*)malloc(sizeof(res));
    result->head = first;
    result->tail = head;
    return result;
}

void printList(node* head)
{
    node* prev = NULL;
    node* next;

    while(XOR(prev, head->np) != NULL)
    {
        printf("%d -> ", head->data);
        next = XOR(prev, head->np);
        prev = head;
        head = next;
    }
    printf("%d\n\n", head->data);
}

int search(node* head, int n)
{
    node* prev = NULL;
    node* next;
    int curr = 1;
    while(head != NULL)
    {
        if(head->data == n)
            return curr;
        next = XOR(prev, head->np);
        prev = head;
        head = next;
        curr++;
    }
    return 0;
}

node* insertAtHead(node* head, int data)
{
        node* temp = (node*)malloc(sizeof(node));
        temp->data = data;
        head->np = XOR(temp,XOR(NULL, head->np));
        temp->np = XOR(NULL, head);
        return temp;
}

node* insert(node* head, node* tail, int data, int pos)
{
    node* prev = NULL;
    node* next;
     for(int i=1; i<pos-1; i++)
     {
        next = XOR(prev, head->np);
        prev = head;
        head = next;
     }

     node* temp = (node*)malloc(sizeof(node));
     temp->data = data;
     next = XOR(prev, head->np);
     temp->np = XOR(head, next);
     if(next == NULL) //Insertion at end
     {
        head->np = XOR(prev, temp); //Node after inserted node doesn't need to be changed here
        return temp; //Since element is inserted at the end, tail pointer needs to be updated as well.
     }
     else //Insertion in between
     {
        next->np = XOR(temp, XOR(head, next->np)); //Next node needs to be changed according to temp value
        head->np = XOR(prev, temp);    
        return tail;
     }
}

node* deleteAtHead(node* head)
{
    node* next = XOR(NULL, head->np);
    next->np = XOR(NULL, XOR(head, next->np));
    free(head);
    return next;
}

node* delete(node* head, node* tail, int pos)
{
    node* prev = NULL;
    node* next;
    for(int i=1; i<pos; i++)
    {
        next = XOR(prev, head->np);
        prev = head;
        head = next;
    }
    next = XOR(prev, head->np);
    if(next==NULL)
    {
        prev->np = XOR(XOR(prev->np, head), next);
        free(head);
        return prev;
    }
    else
    {
        next->np = XOR(XOR(head, next->np), prev);
        prev->np = XOR(XOR(prev->np, head), next);
        free(head);
        return tail;
    }
}

res* reverse(node* head, node* tail)
{
   node* temp = head;
   head = tail;
   tail = temp;

   res* result = (res*)malloc(sizeof(res));
   result->head = head;
   result->tail = tail;
   return result;
}

int main()
{
    res* result = createList();
    node* head = result->head;
    node* tail = result->tail;
    int choice = 0;
    int data, pos;

    while(1)
    {
        printf("Menu:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Reverse\n");
        printf("5. Print List\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter element and position at which to insert: ");
                scanf("%d %d", &data, &pos);
                if(pos==1)
                    head = insertAtHead(head, data);
                else
                    tail = insert(head, tail, data, pos);
                printf("\n");
            break;

            case 2:
                printf("Enter position at which to delete: ");
                scanf("%d", &pos);
                if(pos==1)
                    head = deleteAtHead(head);
                else
                    tail = delete(head, tail, pos);
                printf("\n");
            break;

            case 3:
                printf("Enter element to search: ");
                scanf("%d", &data);
                int check = search(head, data);
                if(check == 0)
                    printf("%d is not present in the list\n\n", data);
                else
                    printf("%d is present at position %d\n\n", data, check);
            break;

            case 4:
                result = reverse(head, tail);
                head = result->head;
                tail = result->tail;
                printf("\n");
            break;

            case 5:
                printList(head);
            break;

            case 6:
                exit(0);
            break;

            default:
                printf("Invalid input. Enter again\n\n");
        }
    }
}