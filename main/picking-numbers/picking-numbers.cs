using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static Dictionary<int, int> ReadFrequencyMap()
    {
        Console.ReadLine(); // don't need n
        
        var freqs = new Dictionary<int, int>();

        foreach (var key in Console.ReadLine().Split().Select(int.Parse)) {
            int value;
            freqs.TryGetValue(key, out value);
            freqs[key] = value + 1;
        }
        
        return freqs;
    }
    
    private static int[] GetKeysWithSentinel(Dictionary<int, int> freqs)
            => freqs.Keys.OrderBy(key => key)
                         .Concat(Enumerable.Repeat(int.MaxValue, 1))
                         .ToArray();
    
    private static void Main()
    {
        var freqs = ReadFrequencyMap();
        var keys = GetKeysWithSentinel(freqs);
        
        var best = 0;
        
        foreach (var i in Enumerable.Range(0, keys.Length - 1)) {
            var cur = freqs[keys[i]];
            if (keys[i + 1] == keys[i] + 1) cur += freqs[keys[i + 1]];
            if (best < cur) best = cur;
        }
        
        Console.WriteLine(best);
    }
}
