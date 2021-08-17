using System;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        Console.ReadLine(); // don't need n
        
        var counts = new int[100];
        foreach (var x in Console.ReadLine().Split().Select(int.Parse))
            ++counts[x];
        
        Console.WriteLine(string.Join(" ", counts));
    }
}
