using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    // identify consecutive duplicates, dropping all but the first
    // assumes self does not start with int.MaxValue
    // should be faster than Distinct, where dupes needn't be consecutive
    private static IEnumerable<int> Unique(this IEnumerable<int> self)
    {
        var prev = int.MaxValue;
        
        foreach (var cur in self)
            if (prev != cur) yield return prev = cur;
    }
    
    private static IEnumerable<int> ReadRecordAndNegate()
    {
        Console.ReadLine(); // don't need record lengths n, m
        return Console.ReadLine().Split().Select(score => -int.Parse(score));
    }
    
    private static void Main()
    {
        var scores = ReadRecordAndNegate().Unique().ToArray();
        
        foreach (var alice_score in ReadRecordAndNegate()) {
            var i = Array.BinarySearch(scores, alice_score);
            Console.WriteLine((i < 0 ? ~i : i) + 1);
        }
    }
}
