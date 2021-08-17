/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


class GfG
{
    void buildHeap(final int[] arr, final int n)
    {
        for (int i = n / 2; i != -1; --i) heapify(arr, n, i);
    }

    // To heapify a subtree rooted with node i which is
    // an index in arr[]. n is size of heap
    void heapify(final int[] arr, final int n, int i)
    {
        for (; ; ) {
            final int child = pickChild(arr, n, i);
            if (child == -1 || arr[i] >= arr[child]) break;
            swap(arr, i, child);
            i = child;
        }
    }

    private static int pickChild(final int[] arr, final int n, final int i)
    {
        final int left = i * 2 + 1;
        if (left >= n) return -1;

        final int right = left + 1;
        return right == n || arr[left] >= arr[right] ? left : right;
    }

    private static void swap(final int[] arr, final int i, final int j)
    {
        final int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}
