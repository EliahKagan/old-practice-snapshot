using System;
using System.Linq;

internal static class Solution {
    private static string[] Read()
    {
        var a = new string[int.Parse(Console.ReadLine())];

        foreach (var i in Enumerable.Range(0, a.Length))
            a[i] = Console.ReadLine();

        return a;
    }

    private static void Main()
    {
        var strs = Read();

        foreach (var query in Read())
            Console.WriteLine(strs.Count(s => s == query));
    }
}
