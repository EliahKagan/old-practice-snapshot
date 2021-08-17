using System;
using System.Collections.Generic;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class Solution {
    private static void Main()
    {
        var freq_deltas = new Dictionary<char, int>();

        foreach (var c in Console.ReadLine()) {
            if (freq_deltas.ContainsKey(c)) ++freq_deltas[c];
            else freq_deltas.Add(c, 1);
        }

        foreach (var c in Console.ReadLine()) {
            if (freq_deltas.ContainsKey(c)) --freq_deltas[c];
            else freq_deltas.Add(c, -1);
        }

        Console.WriteLine(freq_deltas.Values.Sum(Math.Abs));
    }
}
