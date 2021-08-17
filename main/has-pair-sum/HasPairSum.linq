<Query Kind="Program" />

internal static class Solution {
    private static bool HasPairSum(this int[] a, int sum)
    {
        var i = 0;
        for (var j = a.Length - 1; i < j; ) {
            var s = a[i] + a[j];
            if (s == sum) return true;
            
            if (s < sum) ++i;
            else --j;
        }
        
        return false;
    }
    
    private static void Main()
    {
        new[] { 1, 2, 3, 9 }.HasPairSum(8).Dump();
        new[] { 2, 2, 4, 4 }.HasPairSum(8).Dump();
    }
}