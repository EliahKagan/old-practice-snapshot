using System;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        Console.ReadLine(); // don't need n
        
        Console.WriteLine(Console.ReadLine().Split()
                                            .GroupBy(int.Parse)
                                            .OrderByDescending(Enumerable.Count)
                                            .ThenBy(g => g.Key)
                                            .First()
                                            .Key);
    }
}
