using System;
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

        throw new ArgumentException("character not in grid");
    }

    private static void DisplayPathToPrincess(int n, string[] grid)
    {
        int bi, bj, pi, pj;
        FindCharacter(grid, n, 'm', out bi, out bj);
        FindCharacter(grid, n, 'p', out pi, out pj);

        for (; bi < pi; ++bi) WriteLine("DOWN");
        for (; bi > pi; --bi) WriteLine("UP");
        
        for (; bj < pj; ++bj) WriteLine("RIGHT");
        for (; bj > pj; --bj) WriteLine("LEFT");
    }

    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());

        var grid = new string[n];
        foreach (var i in Enumerable.Range(0, n)) grid[i] = ReadLine();

        DisplayPathToPrincess(n, grid);
    }
}
