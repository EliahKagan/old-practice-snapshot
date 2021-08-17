using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static IEnumerable<char> Reduce(this IEnumerable<char> s)
    {
        const char sentinel = '\0';

        var prev = sentinel;
        var count = 0; // any value is okay here

        foreach (var cur in s.Concat(Enumerable.Repeat(sentinel, 1))) {
            if (cur == prev) ++count;
            else {
                if (count % 2 != 0) yield return prev;
                prev = cur;
                count = 1;
            }
        }
    }

    private static IEnumerable<char> SuperReduce(this IEnumerable<char> s)
    {
        for (var count = s.Count(); ; ) {
            s = s.Reduce();
            var new_count = s.Count();
            if (new_count == count) return s;
            count = new_count;
        }
    }

    private static void Main()
    {
        var a = Console.ReadLine().Trim().SuperReduce().ToArray();

        if (a.Length == 0)  Console.WriteLine("Empty String");
        else                Console.WriteLine(a);
    }
}
