using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static IEnumerable<int> GetSequence()
    {
        var count = int.Parse(Console.ReadLine());
        return Console.ReadLine().Split(' ').Take(count).Select(int.Parse);
    }

    private static void Main()
    {
        var freqs = new Dictionary<int, int>();
        
        foreach (var k in GetSequence()) {
            if (freqs.ContainsKey(k))
                ++freqs[k];
            else
                freqs.Add(k, 1);
        }

        foreach (var k in GetSequence()) {
            if (freqs.ContainsKey(k))
                --freqs[k];
            else
                freqs.Add(k, -1);
        }

        var a = (from p in freqs where p.Value != 0 select p.Key).ToArray();
        Array.Sort(a);
        Console.WriteLine(string.Join(" ", a));
    }
}
