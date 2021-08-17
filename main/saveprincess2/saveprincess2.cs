#define DEBUG

using System;
using System.Diagnostics.Contracts;
using System.Linq;
using static System.Console;

internal static class Solution {
    private static void FindCharacter( // pun intended
            string[] grid, int n, char c, out int i, out int j)
    {
        for (i = 0; i < n; ++i) {
            j = grid[i].IndexOf(c, 0, n);
            if (j != -1) return;
        }

        i = j = -1; // (-1, -1) indicates character was not found
    }

    private static void NextMove(int n, int r, int c, string[] grid)
    {
        int bi, bj, pi, pj;
        FindCharacter(grid, n, 'm', out bi, out bj);
        FindCharacter(grid, n, 'p', out pi, out pj);
        Contract.Assert(bi == r && bj == c);

        if (bi < pi)        WriteLine("DOWN");
        else if (bi > pi)   WriteLine("UP");
        else if (bj < pj)   WriteLine("RIGHT");
        else if (bj > pj)   WriteLine("LEFT");
    }

    private static void Main()
    {
        var n = int.Parse(ReadLine());
        var bi_bj = Array.ConvertAll(ReadLine().Split(' '), int.Parse);

        var grid = new string[n];
        foreach (var i in Enumerable.Range(0, n)) grid[i] = ReadLine();

        NextMove(n, bi_bj[0], bi_bj[1], grid);
    }
}
