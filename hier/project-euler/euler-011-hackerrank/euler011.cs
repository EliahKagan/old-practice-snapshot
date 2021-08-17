// euler011.cs - Project Euler problem 11: Largest product in a grid
//               HackerRank version, with testing/visualization code retained.
// 
// In accordance with the idea that HackerRank submissions are components of a
// larger software system with pre-validated inputs (otherwise, "competitive
// programming" is significantly less practical), the requirement that grid
// values read from standard input are in the correct format is validated by
// assertions, similar to the way the hard-coded "automatic run" mode data
// (accessed via --builtin) is validated.

#define DEBUG

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;
using System.Numerics;
using System.Text;

[assembly:System.Reflection.AssemblyVersion("2.0.0.0")]

[Serializable]
internal sealed class UnreachableException : NotSupportedException { }

internal static class Config {
    // verbose visual output with a color-highlighted grid
    internal static bool Verbose { get; private set; } = false;

    // use the built-in grid instead of reading input
    internal static bool UseBuiltin { get; private set; } = false;

    // flip the grid horizontaly so columns change sides (useful for testing)
    internal static bool Flip { get; private set; } = false;

    internal static void ProcessCommandLineFlags(ref string[] args)
            => args = RemoveAndProcessFlags(args).ToArray();

    private static IEnumerable<string> RemoveAndProcessFlags(string[] args)
    {
        foreach (var arg in args.Select(s => s.Trim())) {
            if (!arg.StartsWith("-")) {
                if (arg.Length != 0) yield return arg;
                continue;
            }

            var opt = arg.ToLowerInvariant();

            switch (opt) {
            case "--verbose":
            case "-v":
                Verbose = true;
                continue;

            case "--quiet":
            case "-q":
                Verbose = false;
                continue;

            case "--builtin":
            case "-b":
                UseBuiltin = true;
                continue;

            case "--input":
            case "-i":
                UseBuiltin = false;
                continue;

            case "--flip":
            case "-f":
                Flip = true;
                continue;

            case "--no-flip":
            case "-n":
                Flip = false;
                continue;

            default:
                Console.Error.WriteLine("{0}: unrecognized option: \"{1}\"",
                        Environment.GetCommandLineArgs()[0], opt);
                Environment.Exit(2);
                throw new UnreachableException();
            }
        }
    }
}

internal enum Orientation { Horizontal, Vertical, DescendRight, DescendLeft }

internal static class IndicesEx {
    internal static T I<T, U>(this Tuple<T, U> self)
    {
        Contract.Assert(self != null);
        return self.Item1;
    }

    internal static U J<T, U>(this Tuple<T, U> self)
    {
        Contract.Assert(self != null);
        return self.Item2;
    }

    internal static Tuple<int, int> Next(this Tuple<int, int> self,
                                         Orientation orientation)
    {
        Contract.Assert(self != null);

        switch (orientation) {
        case Orientation.Horizontal:    // go from left to right
            return Tuple.Create(self.I(), self.J() + 1);

        case Orientation.Vertical:      // go from top to bottom
            return Tuple.Create(self.I() + 1, self.J());

        case Orientation.DescendRight:  // go from top-left to bottom-right
            return Tuple.Create(self.I() + 1, self.J() + 1);

        case Orientation.DescendLeft:   // go from top-right to bottom-left
            return Tuple.Create(self.I() + 1, self.J() - 1);

        default: throw new UnreachableException();
        }
    }
}

internal static class Indices {
    internal static ISet<Tuple<int, int>> GetAdjacents(
            Tuple<int, int> indices, Orientation orientation, int size)
    {
        Contract.Assert(size >= 0);

        var set = new HashSet<Tuple<int, int>>();

        for (; size-- > 0; indices = indices.Next(orientation))
            set.Add(indices);

        return set;
    }

    internal static ISet<Tuple<int, int>> GetAdjacents(
            int i, int j, Orientation orientation, int size)
    {
        return GetAdjacents(Tuple.Create(i, j), orientation, size);
    }
}

internal static class GridEx {
    internal static int Height<T>(this T[,] self)
    {
        Contract.Assert(self != null);
        return self.GetLength(0);
    }

    internal static int Width<T>(this T[,] self)
    {
        Contract.Assert(self != null);
        return self.GetLength(1);
    }

    internal static IEnumerable<int> RowIndices<T>(this T[,] self)
    {
        Contract.Assert(self != null);
        return Enumerable.Range(0, self.Height());
    }

    internal static IEnumerable<int> ColIndices<T>(this T[,] self)
    {
        Contract.Assert(self != null);
        return Enumerable.Range(0, self.Width());
    }

    internal static T? At<T>(this T[,] self, Tuple<int, int> indices)
            where T : struct
    {
        Contract.Assert(self != null && indices != null);

        if (0 <= indices.I() && indices.I() < self.Height()
                    && 0 <= indices.J() && indices.J() < self.Width())
            return self[indices.I(), indices.J()];

        return null;
    }

    internal static BigInteger? ProductAt(this int[,] self,
                                          ISet<Tuple<int, int>> index_set)
    {
        Contract.Assert(self != null && index_set != null);

        BigInteger? product = BigInteger.One;
        foreach (var indices in index_set) product *= self.At(indices);
        return product;
    }
}

internal static class GridTest {
    internal static bool VerifyFromText(int[,] grid, string text)
    {
        Contract.Assert(grid != null && text != null);

        var sb = new StringBuilder();

        var rowsep = string.Empty;
        foreach (var i in grid.RowIndices()) {
            sb.Append(rowsep);
            rowsep = Environment.NewLine;

            var colsep = string.Empty;
            foreach (var j in grid.ColIndices()) {
                sb.AppendFormat("{0}{1:D2}", colsep, grid[i, j]);
                colsep = " ";
            }
        }

        return sb.ToString() == text;
    }
}

internal static class Grid {
    private const string NewLine = @"
";      // In case this file has a different encoding than the environment.

    private const string NoJagged = "jagged grid not allowed";

    private static string[] GetWords() => Console.ReadLine().Trim().Split(' ');

    internal static int[,] FromConsole() // reads a _square_ grid from stdin
    {
        var w = GetWords();
        var n = w.Length;
        Contract.Assert(n != 0, "grid must be non-empty");
        var grid = new int[n, n];

        for (var i = 0; ; ) {
            foreach (var j in Enumerable.Range(0, n))
                grid[i, j] = int.Parse(w[j]);

            if (++i == n) return grid;

            w = GetWords();
            Contract.Assert(w.Length == n, NoJagged);
        }
    }

    internal static int[,] FromText(string text)
    {
        Contract.Assert(!string.IsNullOrWhiteSpace(text));

        var rows = from line
                   in text.Split(new string[] { NewLine },
                                 StringSplitOptions.None)
                   select line.Split(' ');

        var height = rows.Count();
        var width = rows.First().Length;

        var grid = new int[height, width];

        var i = 0;
        foreach (var row in rows) {
            Contract.Assert(row.Length == width, NoJagged);

            foreach (var j in Enumerable.Range(0, width))
                grid[i, j] = int.Parse(row[j]);

            ++i;
        }

        Contract.Assert(GridTest.VerifyFromText(grid, text));
        return grid;
    }

    private static IEnumerable<Orientation> Orientations
    {
        get {
            return (Orientation[])Enum.GetValues(typeof(Orientation));
        }
    }

    internal static ISet<ISet<Tuple<int, int>>> FindMaxProducts(
            int[,] grid, int adjacent_size, out BigInteger product)
    {
        Contract.Assert(grid != null && adjacent_size > 0);
        Contract.Assert(grid.Height() > 0 && grid.Width() > 0);

        var family = new HashSet<ISet<Tuple<int, int>>>();
        BigInteger? best_product = null;

        foreach (var i in grid.RowIndices()) {
            foreach (var j in grid.ColIndices()) {
                foreach (var o in Orientations) {
                    var set = Indices.GetAdjacents(i, j, o, adjacent_size);
                    var p = grid.ProductAt(set);

                    if (p >= (best_product ?? p)) {
                        if (p > best_product) family.Clear();
                        family.Add(set);
                        best_product = p;
                    }

                    if (adjacent_size == 1) break; // orientations not distinct
                }
            }
        }

        product = best_product.Value;
        return family;
    }
}

internal enum Match { None, Single, Multiple } // must appear in this order

internal static class GridMatch {
    private static readonly Dictionary<Match, ConsoleColor?> match_colors
            = new Dictionary<Match, ConsoleColor?> {
                { Match.None, null },
                { Match.Single, ConsoleColor.Red },
                { Match.Multiple, ConsoleColor.Cyan }
            };

    private static void StartHighlighting(Match match)
    {
        var color = match_colors[match];
        if (color.HasValue) Console.ForegroundColor = color.Value;
    }

    private static void EndHighlighting(Match match)
    {
        if (match_colors[match].HasValue)
            Console.ForegroundColor = ConsoleColor.Gray;
    }

    private static void PrintHighlightedEntry(int value, Match match)
    {
        StartHighlighting(match);
        Console.Write("{0:D2}", value);
        EndHighlighting(match);
    }

    internal static void PrintHighlighted(int[,] grid, Match[,] match_table)
    {
        Contract.Assert(grid != null && match_table != null);

        foreach (var i in grid.RowIndices()) {
            foreach (var j in grid.ColIndices()) {
                if (j != 0) Console.Write(' ');
                PrintHighlightedEntry(grid[i, j], match_table[i, j]);
            }

            Console.WriteLine();
        }
    }

    internal static Match[,] GetMatchTable(
            int[,] grid, ISet<ISet<Tuple<int, int>>> index_family)
    {
        Contract.Assert(grid != null && index_family != null);

        var table = new Match[grid.Height(), grid.Width()];
        
        foreach (var set in index_family) {
            foreach (var indices in set) {
                switch (table[indices.I(), indices.J()]) {
                case Match.None:
                    table[indices.I(), indices.J()] = Match.Single;
                    break;

                case Match.Single:
                    table[indices.I(), indices.J()] = Match.Multiple;
                    break;

                case Match.Multiple: break; // keep the same highlighting
                }
            }
        }

        return table;
    }
}

internal static class Program {
    // Note: GridText is only used if the program is invoked with command-line
    //       arguments that specify testing. In normal operation on HackerRank,
    //       this program does _not_ use any hard-coded input.
    private const string GridText =
@"08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08
49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00
81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65
52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91
22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80
24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50
32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70
67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21
24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72
21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95
78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92
16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57
86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58
19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40
04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66
88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69
04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36
20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16
20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54
01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48";

    private const int DefaultLength = 4;

    private static void ApplyHorizontalFlip(int[,] grid) // cols change sides
    {
        foreach (var j in Enumerable.Range(0, grid.Width() / 2)) {
            var j2 = grid.Width() - j - 1;

            foreach (var i in grid.RowIndices()) {
                var tmp = grid[i, j];
                grid[i, j] = grid[i, j2];
                grid[i, j2] = tmp;
            }
        }
    }

    private static int[,] GetGrid()
    {
        var grid = (Config.UseBuiltin ? Grid.FromText(GridText)
                                      : Grid.FromConsole());

        // if grid dimensions may be changed, change assertion accordingly
        Contract.Assert(grid.Height() == 20 && grid.Width() == 20);

        if (Config.Flip) ApplyHorizontalFlip(grid);
        return grid;
    }

    private static void PrintCalculations(int[,] grid,
            ISet<ISet<Tuple<int, int>>> index_family, BigInteger product)
    {
        foreach (var set in index_family) {
            var sep = string.Empty;
            foreach (var indices in set) {
                Console.Write("{0}{1,2}", sep, grid.At(indices).Value);
                sep = " * ";
            }

            Console.WriteLine(" = {0:R}", product);
        }
    }

    private static int? Parse(string[] args, int min, int max)
    {
        Contract.Assert(args != null && min <= max);

        if (!args.Any()) return null;

        try {
            if (args.Length == 1) {
                var n = int.Parse(args[0]);
                if (min <= n && n <= max) return n;
            }
        }
        catch (FormatException) { }
        catch (OverflowException) { }

        Console.Error.WriteLine("Usage:  {0} [options] [length]",
                                Environment.GetCommandLineArgs()[0]);
        Environment.Exit(1);

        throw new UnreachableException();
    }

    private static void Main(string[] args)
    {
        Config.ProcessCommandLineFlags(ref args);

        var grid = GetGrid();
        var adjacent_bound = Math.Max(grid.Width(), grid.Height());
        var adjacent_size = Parse(args, 1, adjacent_bound) ?? DefaultLength;
        Contract.Assert(adjacent_size <= adjacent_bound);

        BigInteger product;
        var family = Grid.FindMaxProducts(grid, adjacent_size, out product);

        if (!Config.Verbose) {
            Console.WriteLine("{0:R}", product);
            return;
        }

        var match_table = GridMatch.GetMatchTable(grid, family);
        GridMatch.PrintHighlighted(grid, match_table);

        Console.WriteLine();
        PrintCalculations(grid, family, product);
    }
}
