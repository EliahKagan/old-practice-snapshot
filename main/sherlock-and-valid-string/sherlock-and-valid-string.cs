#define DEBUG

using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static void Increment<TKey>(this Dictionary<TKey, int> self,
                                        TKey key)
    {
        if (self.ContainsKey(key))
            ++self[key];
        else
            self.Add(key, 1);
    }

    private static void Exchange<T>(T a, T b)
    {
        var c = a;
        a = b;
        b = c;
    }

    private static bool IsDeemedValid(this string s)
    {
        var freqs = new Dictionary<char, int>();
        foreach (var ch in s) freqs.Increment(ch);

        switch (freqs.Values.Distinct().Count()) {
        case 0: case 1:
            return true;

        case 2:
            // majority: the number of times each of most chars appear in s
            // minority: how many times each of the other chars appear in s

            var freq = freqs.Values.First();
            var majority = freqs.Values.Where(f => f == freq).Count();
            var minority = freqs.Count - majority;
            if (majority < minority) Exchange(majority, minority);



        default:
            return false;
        }
    }

    private static void Main()
    {
        Console.WriteLine(Console.ReadLine().IsDeemedValid() ? "YES" : "NO");
    }
}
