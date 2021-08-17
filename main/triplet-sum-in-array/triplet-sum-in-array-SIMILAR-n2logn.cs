using System;

internal static class Solution {
    private static int CountBeautifulTriplets(int[] a, int d)
    {
        var count = 0;
        
        var istop = a.Length - 1;
        for (var i = 0; i != istop; ++i) {
            var d2 = d - a[i];
            for (var j = i + 1; j != a.Length; ++j) {
                var key = d2 - a[j];
                if (key <= d2) break;
                if (Array.BinarySearch(a, j, a.Length - j, key) >= 0) ++count;
            }
        }
        
        return count;
    }
    
    private static void Main()
    {
        var d = int.Parse(Console.ReadLine().Split()[1]); // don't need n
        var a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        Console.WriteLine(CountBeautifulTriplets(a, d));
    }
}
