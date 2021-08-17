<Query Kind="Program" />

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
        var a = new[] { "1234", "91011", "99100", "101103", "010203", "13", "1" };
        a.Select(FindBeautySeed).Dump();
        "10001".GetPossibleBeautySeeds().Dump();
        "101102103104105106".FindBeautySeed().Dump();
        
        for (var i = 0; i != 10; ++i) {
            var t = string.Join("", Enumerable.Repeat(i.ToString(), 32));
            t.Dump();
            t.FindBeautySeed().Dump();
        }
    }
}
