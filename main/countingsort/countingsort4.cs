using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static IEnumerable<KeyValuePair<int, string>> ReadPairs()
    {
        for (var n = int.Parse(Console.ReadLine()); n > 0; --n) {
            var tok = Console.ReadLine().Split();
            var key = int.Parse(tok[0]);
            yield return new KeyValuePair<int, string>(key, tok[1]);
        }
    }
    
    private static List<int>[] GetEmptyBins(int n)
        => Enumerable.Range(0, n).Select(_ => new List<int>()).ToArray();
    
    // Returns a sorted array of bins of indices in the original array.
    private static List<int>[] CountingSort(KeyValuePair<int, string>[] pairs)
    {
        var bins = GetEmptyBins(100);
        
        foreach (var i in Enumerable.Range(0, pairs.Length))
            bins[pairs[i].Key].Add(i);
        
        return bins;
    }
    
    private static IEnumerable<string>
    GetOutputStrings(KeyValuePair<int, string>[] pairs, List<int>[] bins)
    {
        var half = pairs.Length / 2;
        
        foreach (var bin in bins) {
            foreach (var i in bin)
                yield return i < half ? "-" : pairs[i].Value;
        }
    }
    
    private static void Main()
    {
        var pairs = ReadPairs().ToArray();
        var bins = CountingSort(pairs);
        Console.WriteLine(string.Join(" ", GetOutputStrings(pairs, bins)));
    }
}
