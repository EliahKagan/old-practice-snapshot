using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static long ComputeIntervalArea(IEnumerable<string[]> intervals)
        => from a in intervals
           select new { r = int.Parse(a[0]), c1 = long.Parse(a[1]),
                                             c2 = long.Parse(a[2]) }
           group new { c1, c2 } by r into 
        
        => intervals.Select(a => new { r = int.Parse(a[0]),
                                       c1 = long.Parse(a[1]),
                                       c2 = long.Parse(a[2]) })
                    .GroupBy(x => x.r)
    
    private static void Main()
    {
        var nmk = Console.ReadLine().Split();
        var square_area = long.Parse(nmk[0]) * long.Parse(nmk[1]);
        
        var indices = Enumerable.Range(0, int.Parse(nmk[2]));
        var intervals = indices.Select(_ => Console.ReadLine().Split());
        var interval_area = ComputeIntervalArea(intervals);
        
        Console.WriteLine(square_area - interval_area);
    }
}
