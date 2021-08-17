using System;

[assembly: System.Reflection.AssemblyVersion("2.0.0.0")]

internal static class Solution {
    private static void Main()
    {
        for (var t = ReadValue(); t > 0; --t) {
            Console.ReadLine(); // don't need n
            Console.WriteLine(ReadRecord().CountInversionsFast());
        }
    }

    private static int ReadValue() => int.Parse(Console.ReadLine());

    private static int[] ReadRecord()
    {
        var line = Console.ReadLine();

        var tokens = line.Split((char[])null,
                                StringSplitOptions.RemoveEmptyEntries);

        return Array.ConvertAll(tokens, int.Parse);
    }

    private static int CountInversionsFast(this int[] a) // uses mergesort
    {
        var count = 0;
        var aux = new int[a.Length];

        Action<int, int, int> merge = (left, mid, right) => {
            var i = left;
            var j = mid +  1;
            var k = 0;

            while (i <= mid && j <= right) {
                if (a[i] <= a[j]) {
                    aux[k++] = a[i++];
                } else {
                    count += j - left - k;
                    aux[k++] = a[j++];
                }
            };

            while (i <= mid) aux[k++] = a[i++];

            while (j <= right) aux[k++] = a[j++];

            Array.Copy(aux, 0, a, left, k);
        };

        Action<int, int> mergesort = null;
        mergesort = (left, right) => {
            if (left < right) {
                var mid = left + (right - left) / 2;
                mergesort(left, mid);
                mergesort(mid + 1, right);
                merge(left, mid, right);
            }
        };

        mergesort(0, a.Length - 1);
        return count;
    }
}
