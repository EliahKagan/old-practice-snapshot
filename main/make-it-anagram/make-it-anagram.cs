using System;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        var freqs = new int[26];
        foreach (char ch in Console.ReadLine()) ++freqs[ch - 'a'];
        foreach (char ch in Console.ReadLine()) --freqs[ch - 'a'];
        Console.WriteLine(freqs.Sum(Math.Abs));
    }
}
