using System;
using System.Collections.Generic;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    private static int ReadValue() => int.Parse(Console.ReadLine());

    private static bool[,] ReadGrid()
    {
        var n = ReadValue();
        var m = ReadValue();
        var grid = new bool[n, m];

        for (var i = 0; i != n; ++i) {
            var line = Console.ReadLine();
            for (var j = 0; j != m; ++j)
                if (line[j * 2] == '1') grid[i, j] = true;
        }

        return grid;
    }

    // Returns the measure (i.e., area) of the connected region in grid that
    // contains the cell (i, j). If (i, j) is false (i.e., not part of any
    // region), returns 0. Mutates grid by setting all cells in the region
    // containing (i, j) to false, i.e., removing the region.
    private static int MeasureRegion(this bool[,] grid,
                                     int i, int j, int imax, int jmax)
    {
        if (!grid[i, j]) return 0;

        grid[i, j] = false;
        var a = 1;

        if (i != 0) { // row above
            a += grid.MeasureRegion(i - 1, j, imax, jmax);
            if (j != 0)     a += grid.MeasureRegion(i - 1, j - 1, imax, jmax);
            if (j != jmax)  a += grid.MeasureRegion(i - 1, j + 1, imax, jmax);
        }

        if (i != imax) { // row below
            a += grid.MeasureRegion(i + 1, j, imax, jmax);
            if (j != 0)     a += grid.MeasureRegion(i + 1, j - 1, imax, jmax);
            if (j != jmax)  a += grid.MeasureRegion(i + 1, j + 1, imax, jmax);
        }

        // same row
        if (j != 0)     a += grid.MeasureRegion(i, j - 1, imax, jmax);
        if (j != jmax)  a += grid.MeasureRegion(i, j + 1, imax, jmax);

        return a;
    }

    // Enumerates the measures of each connected region in grid, where a
    // cell is part of a region when it is sets to true. Mutates grid by
    // setting all such cells false (i.e., resets grid to be all false.)
    private static IEnumerable<int> MeasureAllRegions(this bool[,] grid)
    {
        var n = grid.GetLength(0);
        var m = grid.GetLength(1);

        foreach (var i in Enumerable.Range(0, n)) {
            foreach (var j in Enumerable.Range(0, m)) {
                if (grid[i, j])
                    yield return grid.MeasureRegion(i, j, n - 1, m - 1);
            }
        }
    }

    private static void Main()
        => Console.WriteLine(ReadGrid().MeasureAllRegions()
                                       .DefaultIfEmpty()
                                       .Max());
}
