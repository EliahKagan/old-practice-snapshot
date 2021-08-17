<Query Kind="Program">
  <Namespace>static System.Diagnostics.Contracts.Contract</Namespace>
  <Namespace>System</Namespace>
</Query>

internal static class Solution {
    private const int MaxExpenditure = 200;

    private static int[] ReadRecord()
        => Array.ConvertAll(Console.ReadLine().Split(), int.Parse);

    private static int[] ReadParameters(out int total_count,
                                        out int window_size)
    {
        var total_count_and_window_size = ReadRecord();
        total_count = total_count_and_window_size[0];
        window_size = total_count_and_window_size[1];
        Assert(0 < window_size && window_size <= total_count);

        var expenditures = ReadRecord();
        Assert(expenditures.Length == total_count);
        return expenditures;
    }

    private static int[] GetInitialWindowCounts(this int[] expenditures,
                                                int window_size)
    {
        var counts = new int[MaxExpenditure + 1];
        for (var i = 0; i != window_size; ++i) ++counts[expenditures[i]];
        return counts;
    }

    private static int CountTo(this int[] counts, int target, out int excess)
    {
        var value = 0;
        var count = 0;
        while ((count += counts[value]) < target) ++value;

        excess = count - target;
        return value;
    }

    private static void Main()
    {
        int total_count, window_size;
        var expenditures = ReadParameters(out total_count, out window_size);

        var counts = expenditures.GetInitialWindowCounts(window_size);
        int excess;
        var midval = counts.CountTo(window_size / 2 + 1, out excess);
        
        total_count.Dump(nameof(total_count));
        window_size.Dump(nameof(window_size));
        expenditures.Dump(nameof(expenditures));
        Enumerable.Range(0, counts.Length)
                  .Zip(counts, (Value, Count) => new { Value, Count })
                  .Where(row => row.Count != 0)
                  .Dump(nameof(counts));
        midval.Dump(nameof(midval));
        excess.Dump(nameof(excess));
    }
}
