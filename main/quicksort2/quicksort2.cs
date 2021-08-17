using System;

class Solution {
    private static void print(int[] a, int start, int end)
    {
        Console.Write(a[start]);
        while (++start != end) Console.Write($" {a[start]}");
        Console.WriteLine();
    }

    private static void quickSort(int[] a, int start, int end)
    {
        var n = end - start;
        if (n < 2) return;

        var left = new int[n];
        var equal = new int[n];
        var right = new int[n];

        var i = 0;
        var j = 0;
        var k = 0;

        var p = a[start];
        for (var h = start; h != end; ++h) {
            if (a[h] < p)       left[i++] = a[h];
            else if (a[h] == p) equal[j++] = a[h];
            else                right[k++] = a[h];
        }

        var hh = start;
        for (var ii = 0; ii != i;) a[hh++] = left[ii++];
        for (var jj = 0; jj != j;) a[hh++] = equal[jj++];
        for (var kk = 0; kk != k;) a[hh++] = right[kk++];

        quickSort(a, start, start + i);
        quickSort(a, start + i + j, start + i + j + k);
        print(a, start, end);
    }

    private static void quickSort(int[] a) => quickSort(a, 0, a.Length);

    /* Tail starts here */
    static void Main(String[] args)
    {

        int _ar_size;
        _ar_size = Convert.ToInt32(Console.ReadLine());
        int[] _ar = new int[_ar_size];
        String elements = Console.ReadLine();
        String[] split_elements = elements.Split(' ');
        for (int _ar_i = 0; _ar_i < _ar_size; _ar_i++) {
            _ar[_ar_i] = Convert.ToInt32(split_elements[_ar_i]);
        }

        quickSort(_ar);
    }
}
