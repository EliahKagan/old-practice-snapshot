using System;

internal static class Solution {
    private static bool Matches(this string text, string pattern)
    {
        var i = 0;
        
        foreach (var ch in pattern) {
            do
                if (i == text.Length) return false;
            while (ch != text[i++]);
        }
        
        return true;
    }
    
    private static void Main()
    {
        for (var q = int.Parse(Console.ReadLine()); q > 0; --q) {
            Console.WriteLine(Console.ReadLine().Trim()
                                     .Matches("hackerrank") ? "YES" : "NO");
        }
    }
}
