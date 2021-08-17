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

    private static int Walk(this char[][] forest, int i, int j, int count = 0)
    {
        while (forest[i][j] != '*') {
            forest[i][j] = 'X';

            var choices = 0;

            var north = false;
            var east = false;
            var south = false;
            var west = false;

            if (forest[i - 1][j] != 'X') {
                north = true;
                ++choices;
            }

            if (forest[i][j + 1] != 'X') {
                east = true;
                ++choices;
            }

            if (forest[i + 1][j] != 'X') {
                south = true;
                ++choices;
            }

            if (forest[i][j - 1] != 'X') {
                west = true;
                ++choices;
            }

            switch (choices) {
            case 0:
                return -1;

            case 1:
                if (north) --i;
                else if (east) ++j;
                else if (south) ++i;
                else if (west) --j;
                else throw new NotImplementedException("logic error detected");

                continue;

            default:
                if (north) {
                    var ret = forest.Walk(i - 1, j, count + 1);
                    if (ret != -1) return ret;
                }

                if (east) {
                    var ret = forest.Walk(i, j + 1, count + 1);
                    if (ret != -1) return ret;
                }

                if (south) {
                    var ret = forest.Walk(i + 1, j, count + 1);
                    if (ret != -1) return ret;
                }

                if (west) {
                    var ret = forest.Walk(i, j - 1, count + 1);
                    if (ret != -1) return ret;
                }

                return -1;
            }
        }

        return count;
    }

    private static void Main()
    {
        for (var t = ReadValue(); t > 0; --t) {
            int i, j;
            var forest = ReadForest(out i, out j);
            var count = forest.Walk(i, j);
            //Console.WriteLine($"Guess: {ReadValue()}\t\tActual: {count}");
            Console.WriteLine(ReadValue() == count ? "Impressed" : "Oops!");
        }
    }
}
