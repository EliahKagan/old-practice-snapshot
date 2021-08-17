#define DEBUG

using System;
using System.Diagnostics.Contracts;
using System.Linq;
using System.Text.RegularExpressions;

internal static class Solution {
    /// <summary>
    /// Tells if a string is the textual representation of a number falling
    /// within a specified range.
    /// </summary>
    /// <param name="self">The string to interpret as a number. This must
    ///     already be a correct representation for some decimal, or
    ///     System.FormatException is thrown. (But it need not be in the range
    ///     of System.Int32.)</param>
    /// <param name="min">The minimum value of the allowed range.</param>
    /// <param name="max">The maximum value of the allowed range.</param>
    /// <returns></returns>
    private static bool InRange(this string self, decimal min, decimal max)
    {
        Contract.Assert(min <= max);

        try {
            var n = decimal.Parse(self);
            if (min <= n && n <= max) return true;
        }
        catch (OverflowException) { }

        return false;
    }

    private static void Main()
    {
        const string entry_pattern = @"([+-]?(?:0|[1-9]\d*)(?:\.\d+)?)";
        const string pair_format = @"^\s*\({0},\s+{0}\)\s*$";
        var regex = new Regex(string.Format(pair_format, entry_pattern));

        foreach (var i in Enumerable.Range(0, int.Parse(Console.ReadLine()))) {
            var match = regex.Match(Console.ReadLine());

            if (match.Success) {
                Contract.Assert(match.Groups.Count == 3);

                var entries = match.Groups.Cast<Group>()
                                          .Skip(1)
                                          .Select(g => g.Value)
                                          .ToArray();

                if (entries[0].InRange(-90m, 90m)
                            && entries[1].InRange(-180m, 180m)) {
                    Console.WriteLine("Valid");
                    continue;
                }
            }

            Console.WriteLine("Invalid");
        }
    }
}
