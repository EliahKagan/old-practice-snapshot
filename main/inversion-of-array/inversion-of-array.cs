using System;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    private static void Main()
    {
        for (var t = ReadValue(); t > 0; --t) {
            Console.ReadLine(); // don't need n
            Console.WriteLine(ReadRecord().CountInversions());
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

    private static int CountInversions(this int[] a) // uses insertion sort
    {
        var count = 0;

        for (var j = 0; j != a.Length; ++j) {
            var e = a[j];
            var i = j;
            for (; i != 0 && e < a[i - 1]; --i) a[i] = a[i - 1];
            a[i] = e;
            count += j - i;
        }

        return count;
    }
}
