using System;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    private static int BubbleSort(int[] a, int n) // returns number of swaps
    {
        var swap_count = 0;

        for (var i = 0; i < n; ++i) {
            var swaps = 0;

            var imax = n - 1;
            for (var j = 0; j < imax; ++j) {
                if (a[j] > a[j + 1]) {
                    ++swaps;
                    var tmp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = tmp;
                }
            }

            if (swaps == 0) break;
            swap_count += swaps;
        }

        return swap_count;
    }

    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());
        var a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

        Console.WriteLine("Array is sorted in {0} swaps.", BubbleSort(a, n));
        Console.WriteLine("First Element: {0}", a[0]);
        Console.WriteLine("Last Element: {0}", a[n - 1]);
    }
}
