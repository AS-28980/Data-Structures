#include <stdio.h>

void swap(int *a, int *b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Heapify(int arr[], int n, int i) 
{
    int min = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && arr[left] < arr[min])
        min = left;
    if (right < n && arr[right] < arr[min])
        min = right;

    if (min != i) 
    {
        swap(&arr[i], &arr[min]);
        Heapify(arr, n, min);
    }
}

void BuildHeap(int arr[], int n) 
{
    for (int i = n / 2 - 1; i >= 0; i--) 
        Heapify(arr, n, i);
}

int DeleteMin(int arr[], int *n) 
{
    if (*n <= 0) // Empty heap
        return -1;

    if (*n == 1) // Only one element in the heap
    {
        (*n)--;
        return arr[0];
    }

    int root = arr[0];
    arr[0] = arr[(*n) - 1];
    (*n)--;
    Heapify(arr, *n, 0);
    return root;
}

void HeapSort(int arr[], int n) 
{
    BuildHeap(arr, n);

    for (int i = n - 1; i > 0; i--) 
    {
        int min = DeleteMin(arr, &n);
        arr[i] = min;
    }
}

int main() 
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter elements one by one (one on each line):\n");
    
    for(int i=0; i<n; i++)
        scanf("%d", &arr[i]);

    printf("\nOriginal array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    HeapSort(arr, n);

    for(int i=0; i<n/2; i++)
        swap(&arr[i], &arr[n-1-i]);

    printf("\nSorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}
