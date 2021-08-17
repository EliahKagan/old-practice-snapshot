using System;

internal static class Solution {
    private static int ReadState() // number of page turns from page 1
            => int.Parse(Console.ReadLine()) / 2;
    
    private static void Main()
    {
        var last = ReadState();
        var cur = ReadState();
        
        Console.WriteLine(Math.Min(cur, last - cur));
    }
}
