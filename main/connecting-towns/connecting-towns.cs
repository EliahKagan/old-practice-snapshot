#define DEBUG

using System;
using System.Diagnostics.Contracts;
using System.Linq;

internal static class Solution {
    private static int GetNumber() => int.Parse(Console.ReadLine());

    private static int[] GetRecord()
            => Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

    private static void Main()
    {
        for (var t = GetNumber(); t > 0; --t) {
            var count = GetNumber() - 1;
            var routes = GetRecord();
            Contract.Assert(1 < count && count == routes.Length);

            Console.WriteLine(routes.Aggregate((a, b) => a * b % 1234567));
        }
    }
}
