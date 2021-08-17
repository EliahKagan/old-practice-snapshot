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

    private static bool IsDeemedValid(this string s)
    {
        // letter in in s -> how many times it appears in s
        var charfreqs = new Dictionary<char, int>();
        foreach (var c in s) charfreqs.Increment(c);

        // number of times -> number of distinct letters appearing that often
        var freqfreqs = new Dictionary<int, int>();
        foreach (var freq in charfreqs.Values) freqfreqs.Increment(freq);
        
        // 0 or 1 frequencies: valid; more than 2 frequencies: invalid
        if (freqfreqs.Count != 2) return freqfreqs.Count < 2;

        // if we just have to remove 1 occurence of 1 letter: valid
        if (freqfreqs.ContainsKey(1) && freqfreqs[1] == 1) return true;

        // if one letter appears one time more ofren than each other letter,
        // then a single occurrence of that more frequent letter may be removed
        // so all letters appear equally frequently -- such a string is valid
        var freqfreqs_in_key_order = freqfreqs.OrderBy(ff => ff.Key).ToArray();
        var low_freq = freqfreqs_in_key_order[0];
        var high_freq = freqfreqs_in_key_order[1];
        return high_freq.Key - low_freq.Key == 1 && high_freq.Value == 1;
    }

    private static void Main()
    {
        Console.WriteLine(Console.ReadLine().IsDeemedValid() ? "YES" : "NO");
    }
}
