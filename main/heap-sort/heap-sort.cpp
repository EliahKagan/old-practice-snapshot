/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/* Main function to do heap sort. This function uses buildHeap()
   and heapify()
void heapSort(int arr[], int n)  {
    buildHeap(arr, n);
    for (int i=n-1; i>=0; i--)  {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
} */
// The functions should be written in a way that array become sorted
// in increasing order when above heapSort() is called.
// To heapify a subtree rooted with node i which is  an index in arr[].
// n is size of heap. This function  is used in above heapSor()
void heapify(int *const arr, const int n, int i)  {
    for (; ; ) {
        const auto left = i * 2 + 1;
        if (left >= n) break;

        const auto right = left + 1;

        const auto child = (right == n || arr[left] >= arr[right] ? left
                                                                  : right);

        if (arr[i] >= arr[child]) break;
        swap(arr[i], arr[child]);
        i = child;
    }
}
// Rearranges input array so that it becomes a max heap
void buildHeap(int *const arr, const int n)  {
    for (int i = n / 2; i != -1; --i) heapify(arr, n, i);
}
