using System;
using System.IO;
using System.Linq;
using System.Security;

[assembly: System.Reflection.AssemblyVersion("1.0.0.1")]

[Serializable]
internal sealed class UnreachableException : NotSupportedException { }

internal static class Util {
    private static bool IsWindows
        => Environment.OSVersion.Platform.ToString().StartsWith("Win");

    internal static void Die(string message)
    {
        var fullname = Environment.GetCommandLineArgs()[0];

        var name = (fullname.EndsWith(".exe") && IsWindows
                        ? Path.GetFileNameWithoutExtension(fullname)
                        : Path.GetFileName(fullname));

        Console.Error.WriteLine($"{name}: error: {message}");
    }
}

internal static class Input {
    private static int[] ParseRow(string line)
        => line.Split().Select(int.Parse).ToArray();

    private static int[][] ParseGridFromFile(string path)
        => File.ReadLines(path).Select(ParseRow).ToArray();

    internal static int[][] ReadGrid(string path)
    {
        try {
            return ParseGridFromFile(path);
        }
        catch (ArgumentNullException) {
            throw; // would be a bug
        }
        catch (ArgumentException) {
            Util.Die($"\"{path}\" is an ill-formed path");
        }
        catch (DirectoryNotFoundException) {
            Util.Die($"\"{path}\" is an inaccessible path");
        }
        catch (FileNotFoundException) {
            Util.Die($"\"{path}\" does not exist");
        }
        catch (PathTooLongException) {
            Util.Die($"\"{path}\" exceeds the maximum path length");
        }
        catch (IOException e) {
            Util.Die($"can't read grid: {e.Message}");
        }
        catch (FormatException) {
            Util.Die("got non-numeric field");
        }
        catch (OverflowException) {
            Util.Die($"got field out of range {int.MinValue}..{int.MaxValue}");
        }
        catch (UnauthorizedAccessException e) {
            Util.Die(e.Message);
        }
        catch (SecurityException e) {
            Util.Die(e.Message);
        }

        throw new UnreachableException();
    }
}

internal static class Program {
    private const int Unknown = -1;

    private static int[] MakeBlankRow(int i)
        => Enumerable.Repeat(Unknown, i).ToArray();

    private static int[][] MakeBlankGrid(int n)
        => Enumerable.Range(1, n).Select(MakeBlankRow).ToArray();

    private static int ComputeMaxPathSum(int[][] grid)
    {
        var memo = MakeBlankGrid(grid.Length);

        int Dfs(int i, int j)
        {
            if (i == grid.Length) return 0;

            if (memo[i][j] == Unknown) {
                memo[i][j] = grid[i][j] + Math.Max(Dfs(i + 1, j),
                                                   Dfs(i + 1, j + 1));
            }

            return memo[i][j];
        }

        return Dfs(0, 0);
    }

    private static void Main(string[] args)
    {
        if (args.Length > 1) Util.Die("too many arguments");

        var path = (args.Length == 0 ? "p067_triangle.txt" : args[0]);
        var grid = Input.ReadGrid(path);

        try {
            Console.WriteLine(ComputeMaxPathSum(grid));
        }
        catch (IndexOutOfRangeException) {
            Util.Die("the grid has missing entries");
        }
    }
}
