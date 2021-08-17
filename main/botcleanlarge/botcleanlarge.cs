#define DEBUG

using System;
using System.Diagnostics.Contracts;
using System.Collections.Generic;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("0.2.0.0")]

internal static class Solution {
    private static void CheckArguments(IList<char[]> board, int m, int n,
                                       int i, int j)
    {
        Contract.Assert(board != null && 0 <= i && i < m && 0 <= j && j < n);
        Contract.Assert(board.Count == m && board.All(row => row.Length == n));
    }

    private static IList<char[]> ReadBoard(out int m, out int n)
    {
        var board = new List<char[]>();

        for (;;) {
            var row = Console.ReadLine();
            if (row == null || (row = row.TrimEnd()).Length == 0)
                break;
            board.Add(row.ToCharArray());
        }

        Contract.Assert(board.Count != 0);
        Contract.Assert(board[0].Length != 0);
        Contract.Assert(board.Skip(1)
                             .All(row => row.Length == board[0].Length));

        m = board.Count;
        n = board[0].Length;
        return board;
    }

    private static void PrintBoard(IList<char[]> board, int m, int n,
                                   int i, int j)
    {
        CheckArguments(board, m, n, i, j);

        Action<int, int> print_rows = (start, stop) => {
            for (var row_index = start; row_index < stop; ++row_index) {
                Console.Write("  ");
                Console.WriteLine(board[row_index]);
            }
        };

        print_rows(0, i);

        Console.Write("  {0}", new string(board[i], 0, j));
        Console.ForegroundColor = ConsoleColor.Cyan;
        Console.Write(board[i][j] == 'd' ? 'd' : 'b');
        Console.ForegroundColor = ConsoleColor.Gray;
        Console.WriteLine(new string(board[i], j + 1, n - (j + 1)));

        print_rows(i + 1, m);
        Console.WriteLine();
    }

    private static int I(this Tuple<int, int> self) { return self.Item1; }
    private static int J(this Tuple<int, int> self) { return self.Item2; }

    private static IEnumerable<Tuple<int, int>> PointsAtDistance(int distance)
    {
        Contract.Assert(distance >= 0);

        for (var i = -distance; i <= distance; ++i) {
            var j = Math.Abs(i) - distance;
            yield return Tuple.Create(i, j);
            if (j != 0)
                yield return Tuple.Create(i, -j);
        }
    }

    private static IEnumerable<Tuple<int, int>>
    PointsAtDistance(int distance, int from_i, int from_j, int m, int n)
    {
        Contract.Assert(0 <= from_i && from_i < m);
        Contract.Assert(0 <= from_j && from_j < n);

        return PointsAtDistance(distance)
                .Select(p => Tuple.Create(from_i + p.I(), from_j + p.J()))
                .Where(q => 0 <= q.I() && q.I() < m
                         && 0 <= q.J() && q.J() < n);
    }

    private static IEnumerable<Tuple<int, int>>
    DirtyPointsAtDistance(IList<char[]> board,
                          int distance, int from_i, int from_j, int m, int n)
    {
        CheckArguments(board, m, n, from_i, from_j);

        return PointsAtDistance(distance, from_i, from_j, m, n)
                .Where(p => board[p.I()][p.J()] == 'd');
    }

    // NextMove() returns true if the bot was able to make a move, and false if
    // there are no more moves -- which means the bot won the game, or there is
    // a bug. Since making multiple moves per run of the program is only for
    // testing, NextMove() doesn't do any caching optimizations.
    private static bool NextMove(IList<char[]> board, int m, int n,
                                 ref int i, ref int j)
    {
        CheckArguments(board, m, n, i, j);

        if (board[i][j] == 'd') {
            board[i][j] = '-';
            Console.WriteLine("CLEAN");
            return true;
        }

        var dmax = m + n - 2; // maximum taxicab distance on an m-by-n grid
        for (var d = 1; d <= dmax; ++d) {
            // select one of the dirty points a distance d away, if any exist
            foreach (var p in DirtyPointsAtDistance(board, d, i, j, m, n)) {
                if (p.I() < i) {
                    --i;
                    Console.WriteLine("UP");
                }
                else if (p.I() > i) {
                    ++i;
                    Console.WriteLine("DOWN");
                }
                else if (p.J() < j) {
                    --j;
                    Console.WriteLine("LEFT");
                }
                else if (p.J() > j) {
                    ++j;
                    Console.WriteLine("RIGHT");
                }
                else
                    Contract.Assert(false, "can't go where we already are");

                return true; //-V3020 [loop iterates 0 or 1 times, never more]
            }
        }

        return false;
    }

    private static void ReadCoords(out int i, out int j)
    {
        var ij = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        Contract.Assert(ij.Length == 2);

        i = ij[0];
        j = ij[1];
    }

    private static void Main(string[] args)
    {
        var full_game = (from arg in args select arg.Trim().ToLower())
                        .Contains("--full-game");

        int i, j, h, w, m, n;
        ReadCoords(out i, out j);
        ReadCoords(out h, out w);
        var board = ReadBoard(out m, out n);

        Contract.Assert(0 <= i && i < m && m == h);
        Contract.Assert(0 <= j && j < n && n == w);

        while (NextMove(board, m, n, ref i, ref j) && full_game)
            PrintBoard(board, m, n, i, j);
    }
}
