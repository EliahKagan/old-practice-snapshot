using System;

internal static class Solution {
    private static int Day(this int[] date)     => date[0];
    private static int Month(this int[] date)   => date[1];
    private static int Year(this int[] date)    => date[2];

    private static int[] ReadDate()
    {
        return Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
    }

    private static int CalculateFine(int[] returned, int[] due)
    {
        if (returned.Year() < due.Year()) return 0;
        if (returned.Year() > due.Year()) return 10000;

        if (returned.Month() < due.Month()) return 0;
        if (returned.Month() > due.Month())
            return (returned.Month() - due.Month()) * 500;

        if (returned.Day() <= due.Day()) return 0;
        return (returned.Day() - due.Day()) * 15;
    }

    private static void Main()
    {
        var returned = ReadDate();
        var due = ReadDate();

        Console.WriteLine(CalculateFine(returned, due));
    }
}
