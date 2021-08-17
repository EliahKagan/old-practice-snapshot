#define DEBUG

using System;
using System.Diagnostics.Contracts;

internal static class Solution {
    static void insertionSort(int[] ar)
    {
        for (var size = 2; size <= ar.Length; ++size) {
            var i = size - 1;
            var e = ar[i];

            for (; 0 < i && e < ar[i - 1]; --i)
                ar[i] = ar[i - 1];

            ar[i] = e;

            Console.WriteLine(string.Join(" ", ar));
        }
    }

    static void Main(String[] args)
    {
        var size = int.Parse(Console.ReadLine());
        var ar = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        Contract.Assert(ar.Length == size);
        insertionSort(ar);
    }
}
