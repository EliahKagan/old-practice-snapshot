using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

internal static class Solution {
    private static int[] ReadRecord()
            => Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
    
    private static int[] ReadInput(out int d, out int m)
    {
        var n = int.Parse(Console.ReadLine());
        var s = ReadRecord();
        
        var dm = ReadRecord();
        d = dm[0];
        m = dm[1];
        
        Trace.Assert(s.Length == n);
        return s;
    }
    
    private static IEnumerable<int> ComputeWindowSums(this int[] s, int m)
    {
        var n = s.Length;
        if (m > n) yield break;
        
        var sum = s.Take(m).Sum();
        yield return sum;
        
        for (var i = 0; m != n; ++i, ++m) yield return sum += s[m] - s[i];
    }
    
    private static void Main()
    {
        int d, m;
        
        Console.WriteLine(ReadInput(out d, out m).ComputeWindowSums(m)
                                                 .Count(x => x == d));
    }
}
