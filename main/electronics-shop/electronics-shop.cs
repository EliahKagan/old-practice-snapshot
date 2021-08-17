using System;

internal static class Solution {
    private static int[] GetRecord()
            => Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
    
    private static void Main() // naive brute-force algorithm (n * m <= 10**6)
    {
        var s = GetRecord()[0]; // don't need n, m
        var kbds = GetRecord();
        var usbs = GetRecord();
        
        var best = -1;
        
        foreach (var kbd in kbds) {
            foreach (var usb in usbs) {
                var cur = kbd + usb;
                if (best < cur && cur <= s) best = cur;
            }
        }
        
        Console.WriteLine(best);
    }
}
