#define DEBUG

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;

internal static class Solution {
    /// <summary>
    /// GetQuery() retrieves a query line.
    /// </summary>
    /// <param name="x">x-value (2nd column, 1st after type) from query</param>
    /// <param name="y">y-value (3rd column, 2nd after type) from query </param>
    /// <returns>Query type (1 or 2, for valid input) is returned.</returns>
    private static int GetQuery(out int x, out int y)
    {
        var a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        Contract.Assert(a.Length == 3);

        x = a[1];
        y = a[2];
        return a[0];
    }

    /// <summary>
    /// Run() runs type #1 and #2 query operations (including printing).
    /// </summary>
    /// <param name="n">number of sequences (N in problem description)</param>
    /// <param name="q">number of queries (Q in problem description)</param>
    /// <param name="lastans">initial value of lastans "register"</param>
    private static void Run(int n, int q, int lastans = 0)
    {
        var rows = new List<int>[n];
        foreach (var i in Enumerable.Range(0, n)) rows[i] = new List<int>();
        
        foreach (var query_index in Enumerable.Range(0, q)) {
            int x, y;
            var t = GetQuery(out x, out y);
            var i = (x ^ lastans) % n;

            switch (t) {
            case 1:
                rows[i].Add(y);
                break;

            case 2:
                var size = rows[i].Count;
                lastans = rows[i][y % size];
                Console.WriteLine(lastans);
                break;
            }
        }
    }

    /// <summary>
    /// Main method, used to obtain N and Q values and call Run() for queries.
    /// </summary>
    private static void Main()
    {
        var n_q = Console.ReadLine().Split(' ').Select(int.Parse);
        Contract.Assert(n_q.Count() == 2);
        Run(n_q.First(), n_q.Last());
    }
}
