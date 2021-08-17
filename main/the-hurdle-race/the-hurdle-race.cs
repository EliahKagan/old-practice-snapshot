using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static IEnumerable<int> GetRecord()
            => Console.ReadLine().Split().Select(int.Parse);
    
    private static void Main()
    {
        var k = GetRecord().ElementAt(1); // don't need n
        Console.WriteLine(Math.Max(0, GetRecord().Max() - k));
    }
}
