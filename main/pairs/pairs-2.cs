using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        var k = int.Parse(Console.ReadLine().Split()[1]); // don't need n
        
        var values = new HashSet<int>();
        var count = 0;
        
        foreach (var x in Console.ReadLine().Split().Select(int.Parse)) {
            if (values.Contains(x - k)) ++count;
            if (values.Contains(x + k)) ++count;
            values.Add(x);
        }
        
        Console.WriteLine(count);
    }
}
