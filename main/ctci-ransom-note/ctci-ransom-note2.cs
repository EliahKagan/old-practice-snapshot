using System;
using System.Collections.Generic;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("0.2.0.0")]

internal static class Solution {
    private static Dictionary<string, int> ReadWordFreqs()
    {
        var freqs = new Dictionary<string, int>();

        foreach (var w in Console.ReadLine().Split(' ')) {
            if (freqs.ContainsKey(w)) ++freqs[w];
            else freqs[w] = 1;
        }

        return freqs;
    }

    private static bool HasSubDict(this Dictionary<string, int> self,
                                   Dictionary<string, int> freqs)
            => freqs.Keys.All(w => self.ContainsKey(w) && freqs[w] <= self[w]);

    private static void Main()
    {
        Console.ReadLine(); // don't need m, n

        var magazine = ReadWordFreqs();
        var note = ReadWordFreqs();

        Console.WriteLine(magazine.HasSubDict(note) ? "Yes" : "No");
    }
}
