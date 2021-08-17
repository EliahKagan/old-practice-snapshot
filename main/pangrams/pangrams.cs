using System;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        const string a = "abcdefghijklmnopqrstuvwxyz";
        var pg = Console.ReadLine().ToLower().Intersect(a).Count() == a.Length;
        Console.WriteLine(pg ? "pangram" : "not pangram");
    }
}
