<Query Kind="Program" />

internal static class Solution {
    private static int PrefixLength(string s, string t)
    {
        var imax = Math.Min(s.Length, t.Length);
        
        var i = 0;
        while (i != imax && s[i] == t[i]) ++i;
        return i;
    }
    
    private static bool CanConvertTo(this string s, string t, int k)
    {
        var comb = s.Length + t.Length;
        var same = PrefixLength(s, t);
        var diff = comb - same * 2;
        
        if (k < diff) return false;
        if (k % 2 == diff % 2) return true;
        if (k > comb) return true;
        return false;
    }
    
    private static string GetWord() => Console.ReadLine().Trim();
    
    private static int GetNum() => int.Parse(Console.ReadLine());
    
    private static void Main()
    {
        var s = GetWord();
        var t = GetWord();
        Console.WriteLine(s.CanConvertTo(t, GetNum()) ? "Yes" : "No");
    }
}
