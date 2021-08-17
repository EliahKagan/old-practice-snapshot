using static System.Console;
using static System.Linq.Enumerable;

internal static class Solution {
    private static void Main()
    {
        const string a = "SOS";
        const int n = 3; // length of "SOS"

        var s = ReadLine().Trim();
        WriteLine(Range(0, s.Length).Count(i => s[i] != a[i % n]));
    }
}
