/*
The dynamic-set operation SET INTERSECTION takes two overlapping
sets S1 and S2 as input, and it returns a set S = S1 ∩ S2 consisting
of all the elements of S1 and S2. The operation usually destroys the
sets S1 and S2. Entries of S1 and S2 can be in any order. Using a
suitable list data structure gives the fastest possible implementation of
SET INTERSECTION.

In this problem for simplicity you can assume that your set
is the set of integers. A pair of sets S1 and S2 are said to be overlapping
if they have some element in common. You need to check which data
structure is suitable for the purpose, and for the problem you need to use
the functionality of that data structure only. You are not allowed to use
a doubly-linked list. If you are using a singly linked list, you have access
to only the head pointer of the list.
*/
#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int data;
    struct node* next;
};
typedef struct node node;

node* createNode(int data) 
{
    node* temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void insertNode(node* head, node* temp) 
{
    while (head->next != NULL) 
    {
        head = head->next;
    }
    head->next = temp;
}

void merge(int arr[], int l, int m, int r) 
{
    int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create temp arrays
	int L[n1], R[n2];

	// Copy data to temp arrays L[] and R[]
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	// Merge the temp arrays back into arr[l..r
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2) 
    {
		if (L[i] <= R[j]) 
        {
			arr[k] = L[i];
			i++;
		}
		else 
        {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of L[],
	// if there are any
	while (i < n1) 
    {
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of R[],
	// if there are any
	while (j < n2) 
    {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(int arr[], int l, int r) 
{
    if (l < r) 
    {
		int m = l + (r - l) / 2;

		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

void printList(node* head) 
{
    while (head != NULL) 
    {
        printf("%d ", head->data);
        head = head->next;
    }
}

int main() 
{
    printf("Enter number of elements in set1: ");
    int size1;
    scanf("%d", &size1);
    int set1[size1];
    printf("Enter elements:\n");
    for (int i = 0; i < size1; i++) 
    {
        scanf("%d", &set1[i]);
    }
    printf("\n");

    printf("Enter number of elements in set2: ");
    int size2;
    scanf("%d", &size2);
    int set2[size2];
    printf("Enter elements:\n");
    for (int i = 0; i < size2; i++) 
    {
        scanf("%d", &set2[i]);
    }
    printf("\n");

    mergeSort(set1, 0, size1 - 1);
    mergeSort(set2, 0, size2 - 1);

    node* head = NULL; // Linked list to store the intersection

    int i = 0, j = 0;
    while (i < size1 && j < size2) 
    {
        if (set1[i] == set2[j]) 
        {
            if (head == NULL) 
            {
                head = createNode(set1[i]);
            } 
            else 
            {
                insertNode(head, createNode(set1[i]));
            }
            i++;
            j++;
        } 
        else if (set1[i] < set2[j]) 
        {
            i++;
        } 
        else 
        {
            j++;
        }
    }

    printf("Elements of intersection:\n");
    printList(head);

    // Clean up memory by freeing the linked list
    while (head != NULL) 
    {
        node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
