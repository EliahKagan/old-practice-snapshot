#define DEBUG

using System;
using System.Diagnostics.Contracts;

internal static class Solution {
    static int InsertionSort(int[] ar) // returns number of shifts performed
    {
        var n = 0;

        for (var size = 2; size <= ar.Length; ++size) {
            var i = size - 1;
            var e = ar[i];

            for (; 0 < i && e < ar[i - 1]; --i, ++n)
                ar[i] = ar[i - 1];

            ar[i] = e;
        }

        return n;
    }

    static void Main(String[] args)
    {
        var size = int.Parse(Console.ReadLine());
        var ar = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        Contract.Assert(ar.Length == size);
        Console.WriteLine(InsertionSort(ar));
    }
}
