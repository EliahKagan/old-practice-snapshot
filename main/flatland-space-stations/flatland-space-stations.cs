using System;
using System.Linq;

internal static class Solution {
    /// <summary>
    /// Reads a record of int fields and return it as an array.
    /// </summary>
    /// <returns>An array representing the record.</returns>
    private static int[] GetRecord()
            => Array.ConvertAll(Console.ReadLine().Trim().Split(' '),
                                int.Parse);

    /// <summary>
    /// Finds the maximum int in an array or parameter list.
    /// </summary>
    /// <param name="values">int values to compare for maximum.</param>
    /// <returns>The highest value found.</returns>
    private static int MaxVal(params int[] values) => values.Max();

    /// <summary>
    /// Finds the maximum step (i.e., maximum of c[i + 1] - c[i]) in an array.
    /// </summary>
    /// <param name="c">Nonempty from which deltas will be computed by
    /// subtraction. (Most useful when c is monotone increasing.)</param>
    /// <param name="m">The number of elements in c to consider.</param>
    /// <returns>The highest difference between subsequent elements, or zero if
    /// the input array contains only one element.</returns>
    private static int MaxDelta(int[] c, int m)
            => Enumerable.Range(0, m - 1)
                         .Select(i => c[i + 1] - c[i])
                         .DefaultIfEmpty()
                         .Max();

    /// <summary>
    /// Finds the maximum distance any city is from an astrodrome (spaceport).
    /// </summary>
    /// <param name="n">Total number of cities.</param>
    /// <param name="m">Number of cities with spaceports.</param>
    /// <param name="c">Sorted array of cities that have spaceports.</param>
    /// <returns>The highest number of 1 km city-to-city steps that must ever
    /// be traversed to get from a city to the nearest city that has a
    /// spaceport (could be zero, if every city has a spaceport).</returns>
    private static int MaxSpaceportDistance(int n, int m, int[] c)
            => MaxVal(c[0], n - 1 - c[m - 1], MaxDelta(c, m) / 2);

    private static void Main()
    {
        var nm = GetRecord();
        var c = GetRecord();
        Array.Sort(c);
        Console.WriteLine(MaxSpaceportDistance(nm[0], nm[1], c));
    }
}
