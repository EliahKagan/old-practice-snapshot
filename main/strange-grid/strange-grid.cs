using System;
using static System.Math;

internal static class Solution {
    private static void Main()
    {
        long[] a = Array.ConvertAll(Console.ReadLine().Split(' '), long.Parse);
        long r = a[0], c = a[1], offset, decade = DivRem(r - 1, 2, out offset);
        Console.WriteLine(decade * 10 + offset + (c - 1) * 2);
    }
}
