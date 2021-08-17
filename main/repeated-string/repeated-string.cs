using System.Collections.Generic;
using System.Linq;
using static System.Console;

internal static class Solution {
    private static int Tally(this IEnumerable<char> chars)
            => chars.Count(c => c == 'a');

    private static void Main()
    {
        var s = ReadLine().Trim();
        var n = long.Parse(ReadLine());
        long m = s.Length;

        var from_full = s.Tally() * (n / m);
        var from_part = s.Take((int)(n % m)).Tally();

        WriteLine(from_full + from_part);
    }
}
