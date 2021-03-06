// C program for insertion sort
#include <stdio.h>
#include <math.h>

void insert(int arr[], int i);

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n) // modified for debugging
{
    void printArray(int *, int);

    int i;
    for (i = 1; i <= n; i++) {
        printArray(arr, n);
        insert(arr, i);
    }
}



/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Driver program to test above functions
int main()
{
    int arr[1000], n, T, i;

    scanf("%d", &T);

    while (T--) {

        scanf("%d", &n);

        for (i = 0; i<n; i++)
            scanf("%d", &arr[i]);

        insertionSort(arr, n);
        printArray(arr, n);
        putchar('\n'); // added for debugging purposes
    }
    return 0;
}

/* The task is to complete insert() which is used 
   as shown below to implement insertionSort() */

/* Function to sort an array using insertion sort
void insertionSort(int arr[], int n)
{
   int i;
   for (i = 1; i < n; i++)
      insert(arr, i);
} */

void insert(int arr[], int i)
{
    const int e = arr[--i];
    for (; i != 0 && e < arr[i - 1]; --i) arr[i] = arr[i - 1];
    arr[i] = e;
}
