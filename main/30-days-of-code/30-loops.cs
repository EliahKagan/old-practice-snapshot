using System.Linq;
using static System.Console;

internal static class Solution {
    private static void Main()
    {
        var n = int.Parse(ReadLine());

        foreach (var i in Enumerable.Range(1, 10))
            WriteLine($"{n} x {i} = {n * i}");
    }
}
