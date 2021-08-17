using System;

internal static class Solution {
    private static void Main()
    {
        try {
            Console.WriteLine(int.Parse(Console.ReadLine()));
            return;
        }
        catch (FormatException) { }
        catch (OverflowException) { }

        Console.WriteLine("Bad String");
    }
}
