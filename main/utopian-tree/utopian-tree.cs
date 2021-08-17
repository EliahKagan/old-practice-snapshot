#define DEBUG // with N <= 60, assertions shouldn't exceed time constraints

using System;
using System.Diagnostics.Contracts;
using System.Linq;

[Serializable]
internal sealed class UnreachableException : NotSupportedException { }

internal static class UtopianTree {
    /// <summary>
    /// Seasons during which the Utopian Tree grows.
    /// </summary>
    internal enum Season { Spring, Summer }

    /// <summary>
    /// Finds the height of the Utopian Tree.
    /// </summary>
    /// <param name="n">number of cycles</param>
    /// <param name="h">initial height, in meters</param>
    /// <param name="s">starting season</param>
    /// <returns>new height, in meters</returns>
    internal static int Height(int n, int h = 1, Season s = Season.Spring)
    {
        Contract.Assert(n >= 0 && h > 0);

        if (n == 0) return h;

        checked {
            switch (s) {
            case Season.Spring:
                return Height(n - 1, h * 2, Season.Summer);
            case Season.Summer:
                return Height(n - 1, h + 1, Season.Spring);
            }
        }

        throw new UnreachableException();
    }
}

internal static class Solution {
    private static int Get()
    {
        return int.Parse(Console.ReadLine());
    }

    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, Get()))
            Console.WriteLine(UtopianTree.Height(Get()));
    }
}
