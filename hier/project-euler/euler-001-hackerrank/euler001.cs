using static System.Console;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    private static long Sum(long to) => (to - 1L) * to / 2L;

    private static long Sum(long to, long by)
            => Sum(to / by + (to % by == 0L ? 0L : 1L)) * by;

    private static long Sum(long to, long by1, long by2)
            => Sum(to, by1) + Sum(to, by2) - Sum(to, by1 * by2);

    private static void Main()
    {
        const long a = 3L, b = 5L; // factors

        for (var t = int.Parse(ReadLine()); t > 0; --t)
            WriteLine(Sum(long.Parse(ReadLine()), a, b));
    }
}
