using System;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());
        var a = Console.ReadLine().Split().Select(int.Parse).Take(n).ToArray();
        Array.Sort(a);

        for (var i = 0; i != n; ) {
            Console.WriteLine(n - i);
            var cut = a[i];
            while (i != n && a[i] <= cut) ++i;
            for (var j = i; j != n; ++j) a[j] -= cut;
        }
    }
}
