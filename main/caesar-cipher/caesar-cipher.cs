using System;
using System.Linq;

internal static class Caesar {
    private const int LowerA = (int)'a', UpperA = (int)'A';

    private static char Rotate(char c, int a, int k)
    {
        return (char)(a + ((int)c - a + k) % 26);
    }

    private static char Rotate(char c, int k)
    {
        if (char.IsLower(c)) return Rotate(c, LowerA, k);
        if (char.IsUpper(c)) return Rotate(c, UpperA, k);
        return c;
    }

    internal static string Rotate(string s, int k)
    {
        return new string(s.Select(c => Rotate(c, k)).ToArray());
    }
}

internal static class Solution {
    private static int ReadNum()
    {
        return int.Parse(Console.ReadLine());
    }

    private static void Main()
    {
        var n = ReadNum();
        var s = Console.ReadLine().Substring(0, n);
        Console.WriteLine(Caesar.Rotate(s, ReadNum()));
    }
}
