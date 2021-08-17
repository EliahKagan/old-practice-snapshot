using System;
using System.Linq;

internal static class Solution {
    private static int CountNeededChanges(string s)
    {
        var n = s.Length;
        if (n % 2 != 0) return -1;

        var m = n / 2;
        var a = new int[26];

        foreach (var i in Enumerable.Range(0, m)) ++a[s[i] - 'a'];
        foreach (var i in Enumerable.Range(m, m)) --a[s[i] - 'a'];

        return a.Where(k => k > 0).Sum();
    }

    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, int.Parse(Console.ReadLine())))
            Console.WriteLine(CountNeededChanges(Console.ReadLine()));
    }
}
