using System;

internal static class Solution {
    private static void Main()
    {
        Console.ReadLine(); // don't need n
        var a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        Array.Sort(a);
        
        for (var i = a.Length - 1; i > 1; --i) {
            if (a[i - 2] + a[i - 1] > a[i]) {
                Console.WriteLine($"{a[i - 2]} {a[i - 1]} {a[i]}");
                return;
            }
        }
        
        Console.WriteLine("-1");
    }
}
