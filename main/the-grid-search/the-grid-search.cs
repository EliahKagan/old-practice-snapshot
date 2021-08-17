using System;
using System.Diagnostics.Contracts;
using System.Linq;

internal static class Solution {
    private static string[] GetGrid(out int rows, out int cols)
    {
        var dims = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

        rows = dims[0];
        cols = dims[1];

        var grid = new string[rows];
        for (var i = 0; i != rows; ++i) grid[i] = Console.ReadLine();
        return grid;
    }

    private static bool SameSubGrid(string[] lhs, int lhs_i, int lhs_j,
                                    string[] rhs, int rhs_i, int rhs_j,
                                    int rows, int cols)
    {
        for (var lhs_m = lhs_i + rows; lhs_i != lhs_m; ++lhs_i, ++rhs_i) {
            if (lhs[lhs_i].Substring(lhs_j, cols)
                        != rhs[rhs_i].Substring(rhs_j, cols))
                return false;
        }

        return true;
    }

    private static bool HasSubGrid(string[] major, int major_rows, int major_cols,
                                   string[] minor, int minor_rows, int minor_cols)
    {
        Contract.Assert(major != null && minor != null);
        Contract.Assert(0 < minor_rows && minor_rows <= major_rows);
        Contract.Assert(0 < minor_cols && minor_cols <= major_cols);

        var minor_rows_after_first = minor_rows - 1;
        var m = major_rows - minor_rows + 1;
        var n = major_cols - minor_cols + 1;

        for (var i = 0; i != m; ++i) {
            for (var j = 0; j < n; ++j) { // note: j also modified in loop body
                j = major[i].IndexOf(minor[0], j);
                if (j == -1) break;

                if (SameSubGrid(major, i + 1, j, minor, 1, 0,
                                minor_rows_after_first, minor_cols))
                    return true;
            }
        }

        return false;
    }

    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, int.Parse(Console.ReadLine()))) {
            int major_rows, major_cols, minor_rows, minor_cols;
            var major = GetGrid(out major_rows, out major_cols);
            var minor = GetGrid(out minor_rows, out minor_cols);

            Console.WriteLine(
                    HasSubGrid(major, major_rows, major_cols,
                               minor, minor_rows, minor_cols) ? "YES" : "NO");
        }
    }
}
