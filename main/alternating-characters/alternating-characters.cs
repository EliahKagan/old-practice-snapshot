using System;
using System.Text.RegularExpressions;

internal static class Solution {
    private static void Main()
    {
        var regex = new Regex(@"(.)(?=\1)", RegexOptions.Compiled);

        for (var t = int.Parse(Console.ReadLine()); t > 0; --t)
            Console.WriteLine(regex.Matches(Console.ReadLine()).Count);
    }
}
