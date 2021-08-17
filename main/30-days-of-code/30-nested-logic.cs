using static System.Console;

internal static class Solution {
    private static int Day(int[] date)   => date[0];
    private static int Month(int[] date) => date[1];
    private static int Year(int[] date)  => date[2];

    private static int[] ReadDate()
            => System.Array.ConvertAll(ReadLine().Split(' '), int.Parse);

    private static int CalculateFine(int[] returned, int[] due)
    {
        if (Year(returned) < Year(due)) return 0;
        if (Year(returned) > Year(due)) return 10000;

        if (Month(returned) < Month(due)) return 0;
        if (Month(returned) > Month(due))
            return (Month(returned) - Month(due)) * 500;

        if (Day(returned) <= Day(due)) return 0;
        return (Day(returned) - Day(due)) * 15;
    }

    private static void Main()
            => WriteLine(CalculateFine(ReadDate(), ReadDate()));
}
