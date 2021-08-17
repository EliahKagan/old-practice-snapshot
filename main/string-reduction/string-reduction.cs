using System;
using System.Diagnostics.Contracts;
using System.Linq;

internal static class Solution {
    private static int ReducedLength(string s)
    {
        var n = s.Length;
        Contract.Assert(n != 0, "string is empty");

        var a = 0;
        var b = 0;
        var c = 0;

        foreach (var ch in s) {
            switch (ch) {
                case 'a':   ++a;    break;
                case 'b':   ++b;    break;
                case 'c':   ++c;    break;

                default:    Contract.Assert(false, "char not a,b,c");   break;
            }
        }

        if (a == n || b == n || c == n) return n;
        var m = a % 2;
        return (b % 2 == m && c % 2 == m) ? 2 : 1;
    }

    private static void Main()
    {
        foreach (var i in Enumerable.Range(0, int.Parse(Console.ReadLine())))
            Console.WriteLine(ReducedLength(Console.ReadLine()));
    }
}
