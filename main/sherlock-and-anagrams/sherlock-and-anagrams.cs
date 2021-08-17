using System;
using System.Collections.Generic;
using System.Linq;

internal static class AnagramCombinatorics {
    private static void Increment<T>(this Dictionary<T, int> dict, T key)
    {
        int n;
        if (dict.TryGetValue(key, out n)) ++dict[key];
        else dict.Add(key, 1);
    }
    
    private static string Alphabetize(this string s, int i, int len)
    {
        var a = s.Substring(i, len).ToCharArray();
        Array.Sort(a);
        return new string(a);
    }
    
    internal static int CountAnagramPairs(this string s)
    {
        var pairs = 0;
        
        foreach (var len in Enumerable.Range(1, s.Length - 1)) {
            var freqs = new Dictionary<string, int>();
            
            foreach (var i in Enumerable.Range(0, s.Length - len + 1))
                freqs.Increment(s.Alphabetize(i, len));
            
            pairs += freqs.Values.Sum(n => n * (n - 1) / 2);
        }
        
        return pairs;
    }
}

internal static class Solution {
    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, int.Parse(Console.ReadLine())))
            Console.WriteLine(Console.ReadLine().Trim().CountAnagramPairs());
    }
}
