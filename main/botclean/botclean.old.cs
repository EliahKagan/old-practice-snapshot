#define DEBUG

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.IO;
using System.Linq;

internal static struct Coords {
    public int I, J;

    public Coords(int i, int j)
    {
        I = i;
        J = j;
    }

    public Coords(System.IO.TextReader input)
    {
        var ij = Array.ConvertAll(input.ReadLine().Split(' '), int.Parse);
        I = ij[0];
        J = ij[1];
    }
}

internal static class Solution {
    private static bool TryCleanAt(this string[] board, Coords pos)
    {
        if (board[pos.I][pos.J] == 'd') {
            board[pos.I][pos.J] = '-';
            Console.WriteLine("CLEAN");
            return true;
        }

        return false;
    }

    private static long Priority(this Coords from, Coords to)
    {
        var priority = ((long)Math.Abs(from.I - to.I)
                        + (long)Math.Abs(from.J - to.J)) << 4
    }

    // Since performing multiple moves per program run is only for testing,
    // NextMove() does not carry out the obvious caching optimization.
    private static bool NextMove(this string[] board, ref Coords pos)
    {
        // if the current position is dirty, just clean it
        if (board.TryCleanAt(pos)) return true;

        // map the dirt
        var dirt = new HashSet<Coords>();
        foreach (var i in Enumerable.Range(0, board.Length)) {
            foreach (var j in Enumerable.Range(0, board.Length))
                if (board[i][j] == 'd') dirt.Add(new Coords(i, j));
        }
        
        // find some dirt, greedily
        //dirt.Min()
    }

    private static string[] ReadBoard() // to faciliate testing, requires board
    {                                   // be square but not necessarily 5x5
        var row = Console.ReadLine().TrimEnd();
        var n = row.Length;
        Contract.Assert(n > 0);
        var board = new string[n];
        board[0] = row;

        foreach (var i in Enumerable.Range(1, n - 1)) {
            row = Console.ReadLine().TrimEnd();
            Contract.Assert(row.Length == n);
            board[i] = row;
        }

        return board;
    }

    private static void Main(string[] args)
    {
        var full_game = (args.Length != 0
                         && args[0].Trim().ToLower() == "--full-game");

        var pos = new Coords(System.Console.In);
        var board = ReadBoard();

        Contract.Assert(0 <= pos.I && pos.I <= board.Length);
        Contract.Assert(0 <= pos.J && pos.J <= board.Length);

        while (board.NextMove(ref pos) && full_game) { }
    }
}
