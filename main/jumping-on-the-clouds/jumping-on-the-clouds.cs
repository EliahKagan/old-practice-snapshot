using System.Collections.Generic;
using static System.Console;
using static System.Linq.Enumerable;

internal static class Solution {
    private static IEnumerable<int> GetRecord()
            => ReadLine().Split(' ').Select(int.Parse);

    private static IEnumerable<int>
    WithSentinelThundercloud(this IEnumerable<int> clouds)
            => clouds.Concat(Repeat(1, 1));

    private static void Main()
    {
        var max_height = int.Parse(ReadLine()) - 1;
        var clouds = GetRecord().WithSentinelThundercloud().ToArray();

        var jumps = 0;
        for (var height = 0; height != max_height; ++jumps)
            if (clouds[height += 2] != 0) --height;

        WriteLine(jumps);
    }
}
