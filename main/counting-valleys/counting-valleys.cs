using System;

internal static class Solution {
    private static void Main()
    {
        Console.ReadLine(); // don't need n
        
        var height = 0;
        var valleys = 0;
        
        foreach (var step in Console.ReadLine().Trim()) {
            switch (step) {
            case 'U':
                if (++height == 0) ++valleys;
                continue;
            case 'D':
                --height;
                continue;
            }
        }
        
        Console.WriteLine(valleys);
    }
}
