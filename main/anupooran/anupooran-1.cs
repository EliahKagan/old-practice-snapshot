using System;

internal static class Solution {
    private static void Main()
    {
        const long b = 10L;
        
        for (var t = int.Parse(Console.ReadLine()); t > 0; --t) {
            var n = long.Parse(Console.ReadLine());
            
            var p = b;
            while (p <= n) p *= b;
            Console.WriteLine(p - n);
        }
    }
}
