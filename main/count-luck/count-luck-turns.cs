using System;
using System.Linq;

internal static class Solution {
    private static int ReadValue() => int.Parse(Console.ReadLine());

    private static char[][] ReadForest(out int starti, out int startj)
    {
        starti = startj = -1;

        var nm = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        var n = nm[0];
        var m = nm[1];

        var forest = new char[n + 2][];
        forest[0] = forest[n + 1] = Enumerable.Repeat('X', m + 2).ToArray();

        var found_start = false;

        for (var i = 0; i != n; ++i) {
            var s = Console.ReadLine().Trim();
            forest[i + 1] = $"X{s}X".ToCharArray();

            if (found_start) continue;

            var j = s.IndexOf('M');

            if (j != -1) {
                starti = i + 1;
                startj = j + 1;
                found_start = true;
            }
        }

        return forest;
    }

    private static string Walk(this char[][] forest,
                               int i, int j, string path = "")
    {
        switch (forest[i][j]) {
            case 'X':
                return null;

            case '*':
                return path;

            default:
                forest[i][j] = 'X';

                return forest.Walk(i - 1, j, path + 'N')
                    ?? forest.Walk(i, j + 1, path + 'E')
                    ?? forest.Walk(i + 1, j, path + 'S')
                    ?? forest.Walk(i, j - 1, path + 'W');
        }
    }

    private static int CountTurns(this string path)
    {
        var count = 0;

        var i = 0;
        for (var j = 1; j < path.Length; ++i, ++j)
            if (path[i] != path[j]) ++count;

        return count;
    }

    private static void Main()
    {
        for (var t = ReadValue(); t > 0; --t) {
            int i, j;
            var forest = ReadForest(out i, out j);
            var count = forest.Walk(i, j).CountTurns();
            Console.WriteLine(ReadValue() == count ? "Impressed" : "Oops!");
        }
    }
}
