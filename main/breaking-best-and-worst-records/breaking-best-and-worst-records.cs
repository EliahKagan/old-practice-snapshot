using System;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        Console.ReadLine(); // don't need n
        
        var hi = int.MinValue;
        var lo = int.MaxValue;
        var his = -1;
        var los = -1;
        
        foreach (var score in Console.ReadLine().Split().Select(int.Parse)) {
            if (hi < score) {
                hi = score;
                ++his;
            }
            
            if (lo > score) {
                lo = score;
                ++los;
            }
        }
        
        Console.WriteLine($"{his} {los}");
    }
}
