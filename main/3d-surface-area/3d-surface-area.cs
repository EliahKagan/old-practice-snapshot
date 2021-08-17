using System;
using System.Collections.Generic;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    private static string[] ReadTokens(int count)
    {
        var line = Console.ReadLine();

        var tokens = line.Split((char[])null,
                                StringSplitOptions.RemoveEmptyEntries);

        if (tokens.Length != count) {
            throw new ArgumentException(message: "wrong record length",
                                        paramName: nameof(count));
        }

        return tokens;
    }

    private static IEnumerable<int> ReadValues(int count)
        => ReadTokens(count).Select(int.Parse);

    private static int[,] ReadPaddedMatrix(int height, int width)
    {
        var grid = new int[height + 2, width + 2];

        for (var i = 1; i <= height; ++i) {
            using (var en = ReadValues(width).GetEnumerator()) {
                for (var j = 1; j <= width; ++j) {
                    en.MoveNext();
                    grid[i, j] = en.Current;
                }
            }
        }

        return grid;
    }

    private static void Main()
    {
        var dimensions = ReadValues(2).ToList();
        var height = dimensions[0];
        var width = dimensions[1];

        var grid = ReadPaddedMatrix(height, width);

        var area = height * width * 2; // top and bottom faces

        for (var i = 0; i <= height; ++i) {
            for (var j = 0; j <= width; ++j) {
                area += Math.Abs(grid[i, j] - grid[i, j + 1])
                      + Math.Abs(grid[i, j] - grid[i + 1, j]);
            }
        }

        Console.WriteLine(area);
    }
}
