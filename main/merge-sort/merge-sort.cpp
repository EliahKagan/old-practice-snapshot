/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

/* The task is to complete merge() which is used
   in below mergeSort() */
/*   l is for left index and r is right index of the
   sub-array of arr to be sorted
void mergeSort(int arr[], int l, int r) {
    if (l < r)   {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
} */
// Merges two subarrays of arr[].  First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int *const arr, const int l, const int m, const int r)
{
    int aux[r - l + 1];
    auto p = aux;

    auto i = l, j = m + 1;
    while (i <= m && j <= r) *p++ = (arr[i] <= arr[j] ? arr[i++] : arr[j++]);
    while (i <= m) *p++ = arr[i++];
    while (j <= r) *p++ = arr[j++];

    copy(aux, p, arr + l);
}
