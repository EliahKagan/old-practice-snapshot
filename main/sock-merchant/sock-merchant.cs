using System.Linq;
using static System.Console;

[assembly: System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class Solution {
    private static void Main()
    {
        ReadLine(); // don't need n

        WriteLine(ReadLine().Split(' ').GroupBy(int.Parse)
                                       .Sum(g => g.Count() / 2));
    }
}
