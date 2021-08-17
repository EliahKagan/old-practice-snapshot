using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static IEnumerable<string> GetPossibleBeautySeeds(this string t)
    {
        if (t[0] == '0') yield break;
        
        var h = t.Length / 2 + 1;
        for (var i = 1; i != h; ++i) yield return t.Substring(0, i);
    }
    
    private static bool CheckBeautySeed(this string t, string s)
    {
        for (var i = s.Length; ; ) {
            s = (long.Parse(s) + 1).ToString();
            var j = i + s.Length;
            if (j > t.Length || t.Substring(i, s.Length) != s) return false;
            if (j == t.Length) return true;
            i = j;
        }
    }
    
    private static string FindBeautySeed(this string t)
        => t.GetPossibleBeautySeeds().FirstOrDefault(t.CheckBeautySeed);
    
    private static void Main()
    {
        for (var q = int.Parse(Console.ReadLine()); q > 0; --q) {
            var s = Console.ReadLine().Trim().FindBeautySeed();
            Console.WriteLine(s == null ? "NO" : $"YES {s}");
        }
    }
}
