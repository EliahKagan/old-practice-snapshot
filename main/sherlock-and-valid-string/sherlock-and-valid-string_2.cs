using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        var s = Console.ReadLine();
        Contract.Assert(s.All(c => 'a' <= c && c <= 'z'));

        var freqs = Array.CreateInstance(typeof(int),
                                         new[] { 'z' - 'a' + 1 },
                                         new[] { (int)'a' });

        Contract.Assert(freqs.Length == 26);
        Contract.Assert(freqs.Cast<int>().All(k => k == 0));

        foreach (var c in s) ++((int[])freqs)[(int)c];
        var x = ((int[])freqs)[(int)'a'];
    }
}
