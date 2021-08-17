#define DEBUG
//#define DEBUG_MEDIANS // checks computed medians with another (slow) method

using System;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using static System.Diagnostics.Contracts.Contract;

[assembly: System.Reflection.AssemblyVersion("1.1.0.0")]

internal static class Solution {
    private const int MaxValue = 200;

    private static int[] ReadRecord()
        => Array.ConvertAll(Console.ReadLine().Split(), int.Parse);

    private static int[] ReadParameters(out int total_count,
                                        out int window_size)
    {
        var total_count_and_window_size = ReadRecord();
        total_count = total_count_and_window_size[0];
        window_size = total_count_and_window_size[1];
        Assert(0 < window_size && window_size <= total_count);

        var values = ReadRecord();
        Assert(values.Length == total_count);
        return values;
    }

    private static int[] GetInitialWindowCounts(this int[] values,
                                                int window_size)
    {
        var counts = new int[MaxValue + 1];
        for (var day = 0; day != window_size; ++day) ++counts[values[day]];
        return counts;
    }

    private static int CountTo(this int[] counts, int target, out int excess)
    {
        var value = 0;
        var running_count = 0;
        while ((running_count += counts[value]) < target) ++value;

        excess = running_count - target;
        return value;
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    private static int CountToMiddle(this int[] counts,
                                     int window_size, out int excess)
        => counts.CountTo(window_size / 2 + 1, out excess);

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    private static int ComputeDoubledMedian(this int[] counts,
            int window_size, int midval, int excess)
    {
        // The midpoint is exact when the number of elements is odd, or when it
        // is equal to the preceding value (i.e., with nonzero excess).
        if (excess != 0 || window_size % 2 != 0) return midval * 2;

        var value = midval - 1;
        while (counts[value] == 0) --value;
        return midval + value;
    }

    [Conditional("DEBUG_MEDIANS")]  
    private static void CheckDoubledMedian(this int[] values, int window_size,
                                           int day, int doubled_median)
    {
        const bool show_window_values = true;

        var window = new int[window_size];
        Array.Copy(values, day - window_size, window, 0, window_size);
        Array.Sort(window);

        var mid = window_size / 2;
        var result = (window_size % 2 == 0 ? window[mid] + window[mid - 1]
                                           : window[mid] * 2);

        Assert(doubled_median == result,
                $"{nameof(CheckDoubledMedian)} failed: "
                + (show_window_values ? $"({string.Join(" ", window)}) " : "")
                + $"{nameof(window_size)}={window_size}, {nameof(day)}={day}, "
                + $"fast={doubled_median}, slow={result}");
    }

    private static void Main()
    {
        int total_count, window_size;
        var values = ReadParameters(out total_count, out window_size);

        var counts = values.GetInitialWindowCounts(window_size);
        // TODO: computation of initial midval and excess will be moved here

        var notifications = 0;
        for (var day = window_size; day != total_count; ++day) {
            // get yesterday's midval and excess, so the median can be found
            // TODO: update/adjust these values instead of recomputing them
            int excess;
            var midval = counts.CountToMiddle(window_size, out excess);

            // check today's value against yesterday's median
            var doubled_median = counts.ComputeDoubledMedian(window_size,
                                                             midval, excess);
            values.CheckDoubledMedian(window_size, day, doubled_median);
            if (doubled_median <= values[day]) ++notifications;

            // update the counts (TODO: midval and excess will be updated here)
            ++counts[values[day]];
            --counts[values[day - window_size]];
        }

        Console.WriteLine(notifications);
    }
}
