#define DEBUG

using System;
using System.Collections.Generic;
using System.Text;

using static System.Diagnostics.Contracts.Contract;
using static System.Linq.Enumerable;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    const int FuseTime = 3, NormalRulesStart = 2, PlantingPeriod = 2;
    const char EmptySymbol = '.', BombSymbol = 'O';

    private static readonly string Name;
    private static readonly bool Verbose;

    static Solution()
    {
        var argv = Environment.GetCommandLineArgs();
        Name = argv[0];
        Verbose = argv.Skip(1).Any(arg => arg == "-v" || arg == "--verbose");
    }

    private static void Log(string message)
    {
        if (Verbose) Console.Error.WriteLine("{0}: {1}", Name, message);
    }

    private static int[,] ReadGrid(int r, int c)
    {
        var grid = new int[r, c];
        
        foreach (var i in Range(0, r)) {
            var line = Console.ReadLine().Trim();
            if (line.Length != c)
                throw new InvalidOperationException("wrong shape");

            foreach (var j in Range(0, c))
                if (line[j] == BombSymbol) grid[i, j] = FuseTime;
        }

        return grid;
    }

    private static int R(this int[,] grid) => grid.GetLength(0);
    private static int C(this int[,] grid) => grid.GetLength(1);

    private static void Write(this int[,] grid)
    {
        var r = grid.R();
        var c = grid.C();

        foreach (var i in Range(0, r)) {
            var row = Range(0, c).Select(j => grid[i, j] == 0 ? EmptySymbol
                                                              : BombSymbol);
            Console.WriteLine(row.ToArray());
        }
    }

    private static string Serialize(this int[,] grid)
    {
        var r = grid.R();
        var c = grid.C();
        var len = r * c;
        var sb = new StringBuilder(len, len);

        foreach (var i in Range(0, r))
            foreach (var j in Range(0, c)) sb.Append(grid[i, j]);

        return sb.ToString();
    }

    private static int[,] Deserialize(this string state, int r, int c)
    {
        var grid = new int[r, c];

        using (var en = state.GetEnumerator()) {
            foreach (var i in Range(0, r)) {
                foreach (var j in Range(0, c)) {
                    en.MoveNext();
                    grid[i, j] = en.Current - '0';
                }
            }

            Assert(!en.MoveNext(), "state string too long");
        }

        return grid;
    }

    private static bool BlastZonesContain(this int[,] grid, int i, int j)
    {
        var imax = grid.R() - 1;
        var jmax = grid.C() - 1;

        return (i != 0 && grid[i - 1, j] == 1)
            || (i != imax && grid[i + 1, j] == 1)
            || (j != 0 && grid[i, j - 1] == 1)
            || (j != jmax && grid[i, j + 1] == 1);
    }

    // removes destroyed objects *except* detonating bombs
    private static void ClearBlastZones(this int[,] grid)
    {
        var r = grid.R();
        var c = grid.C();

        foreach (var i in Range(0, r)) {
            foreach (var j in Range(0, c)) {
                if (grid[i, j] > 1 && grid.BlastZonesContain(i, j))
                    grid[i, j] = 0;
            }
        }
    }

    // reduce each bomb's timer by one tick (and remove if it would detonate)
    private static void CountDown(this int[,] grid)
    {
        var r = grid.R();
        var c = grid.C();

        foreach (var i in Range(0, r)) {
            foreach (var j in Range(0, c))
                if (grid[i, j] != 0) --grid[i, j];
        }
    }

    private static void BurnFuses(this int[,] grid)
    {
        grid.ClearBlastZones();
        grid.CountDown();
    }

    private static void PlantBombs(this int[,] grid)
    {
        var r = grid.R();
        var c = grid.C();

        foreach (var i in Range(0, r)) {
            foreach (var j in Range(0, c))
                if (grid[i, j] == 0) grid[i, j] = FuseTime;
        }
    }

    private static int? WriteHistory(this int[,] grid, int time,
            List<string> states, Dictionary<string, int> times = null)
    {
        var state = grid.Serialize();
        Assert(states.Count == time, "some previous state wasn't recorded");
        states.Add(state);

        if (times != null) {
            int old_time;
            if (times.TryGetValue(state, out old_time)) return old_time;
            times[state] = time;
        }

        return null;
    }

    // the first two ticks differ from the others and must be manually entered
    private static void PreRun(this int[,] grid, List<string> states)
    {
        grid.WriteHistory(0, states);
        grid.BurnFuses();
        grid.WriteHistory(1, states);
    }

    // the remaining ticks can be simulated automatically
    private static int Run(this int[,] grid, int n,
                           List<string> states, Dictionary<string, int> times)
    {
        for (var time = NormalRulesStart; time <= n; ++time) {
            grid.BurnFuses();
            if (time % PlantingPeriod == 0) grid.PlantBombs();

            var possible_old_time = grid.WriteHistory(time, states, times);
            if (possible_old_time.HasValue) {
                var old_time = possible_old_time.Value;
                Assert(NormalRulesStart <= old_time,
                       $"states weren't periodic yet at {nameof(old_time)}");

                var state_period = time - old_time;
                Assert(state_period > 0,
                       $"nonpositive {nameof(state_period)}!");

                var end_time = old_time + (n - old_time) % state_period;
                Assert(old_time <= end_time && end_time < time,
                       $"{nameof(end_time)} is out of range");

                return end_time;
            }
        }

        return n;
    }

    private static void ReadRCN(out int r, out int c, out int n)
    {
        var rcn = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);

        r = rcn[0];
        c = rcn[1];
        n = rcn[2];
    }

    private static void Main()
    {
        int r, c, n;
        ReadRCN(out r, out c, out n);
        var grid = ReadGrid(r, c);

        var states = new List<string>();
        var times = new Dictionary<string, int>();

        grid.PreRun(states);
        var end_time = grid.Run(n, states, times);
        Log($"{nameof(end_time)}: {end_time}");

        states[end_time].Deserialize(r, c).Write();
    }
}
