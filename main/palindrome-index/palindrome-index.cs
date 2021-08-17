using System;

internal static class Palindromes {
    private static bool HasPalindromeRange(this string s, int i, int j)
    {
        while (i < j)
            if (s[i++] != s[j--]) return false;
        
        return true;
    }
    
    internal static int FindPalindromeIndex(this string s)
    {
        var i = 0;
        var j = s.Length - 1;
        
        while (i < j && s[i] == s[j]) {
            ++i;
            --j;
        }
        
        if (i < j) {
            if (s.HasPalindromeRange(i + 1, j)) return i;
            if (s.HasPalindromeRange(i, j - 1)) return j;
        }
        
        return -1;
    }
}

internal static class Solution {
    
    private static void Main()
    {
        for (var t = int.Parse(Console.ReadLine()); t > 0; --t)
            Console.WriteLine(Console.ReadLine().Trim().FindPalindromeIndex());
    }
}
