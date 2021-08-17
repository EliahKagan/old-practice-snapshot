using System;

internal static class Solution {
    private static void Main()
    {
        for (var t = int.Parse(Console.ReadLine()); t > 0; --t) {
            var q = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
            var a = Math.Abs(q[2] - q[0]);
            var b = Math.Abs(q[2] - q[1]);
            
            if (a == b)     Console.WriteLine("Mouse C");
            else if (a < b) Console.WriteLine("Cat A");
            else            Console.WriteLine("Cat B");
        }
    }
}
