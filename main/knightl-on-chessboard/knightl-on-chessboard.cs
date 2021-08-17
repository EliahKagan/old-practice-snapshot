using System;
using System.Collections.Generic;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    private static IEnumerable<int> GetMoves(int n, int a, int b, int i, int j)
    {
        if (i + a < n) {
            if (j + b < n) {
                yield return i + a;
                yield return j + b;
            }

            if (j - b >= 0) {
                yield return i + a;
                yield return j - b;
            }
        }

        if (i + b < n) {
            if (j + a < n) {
                yield return i + b;
                yield return j + a;
            }

            if (j - a >= 0) {
                yield return i + b;
                yield return j - a;
            }
        }

        if (i - a >= 0) {
            if (j + b < n) {
                yield return i - a;
                yield return j + b;
            }

            if (j - b >= 0) {
                yield return i - a;
                yield return j - b;
            }
        }

        if (i - b >= 0) {
            if (j + a < n) {
                yield return i - b;
                yield return j + a;
            }

            if (j - a >= 0) {
                yield return i - b;
                yield return j - a;
            }
        }
    }

    private static int BreadthFirstSearch(this bool[,] board, int n,
            int a, int b, int i, int j, int fi, int fj)
    {
        var q = new Queue<int>();
        q.Enqueue(i);
        q.Enqueue(j);

        for (var moves = 0; q.Count != 0; ++moves) {
            for (var len = q.Count / 2; len != 0; --len) {
                i = q.Dequeue();
                j = q.Dequeue();
                if (board[i, j]) continue;
                board[i, j] = true;

                if (i == fi && j == fj) return moves;

                foreach (var k in GetMoves(n, a, b, i, j)) q.Enqueue(k);
            }
        }

        return -1;
    }

    private static int BreadthFirstSearch(this bool[,] board, int n,
                                          int a, int b)
        => board.BreadthFirstSearch(n, a, b, 0, 0, n - 1, n - 1);

    private static int[][] GetTable(int rows, int cols)
        => Enumerable.Range(0, rows)
                     .Select(_ => new int[cols])
                     .ToArray();

    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());
        var reach = n - 1;
        var table = GetTable(reach, reach);

        for (var r = 0; r != reach; ++r) { // compute off-diagonal elements
            for (var c = r + 1; c != reach; ++c) {
                var board = new bool[n, n];

                table[r][c] = table[c][r]
                            = board.BreadthFirstSearch(n, r + 1, c + 1);
            }
        }

        for (var d = 0; d != reach; ++d) { // optimize diagonal (since a == b)
            var e = d + 1;
            table[d][d] = (reach % e == 0 ? reach / e : -1);
        }

        foreach (var row in table) Console.WriteLine(string.Join(" ", row));
    }
}
