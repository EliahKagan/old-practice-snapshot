using System;
using System.Linq;
using System.Text.RegularExpressions;

internal static class Solution {
    private static void Main()
    {
        const string octet = @"(1?\d?\d|2[0-4]\d|25[0-5])";
        var ipv4pattern = string.Format(@"(?n)^{0}\.{0}\.{0}\.{0}$", octet);
        var ipv4 = new Regex(ipv4pattern);

        const string hexgroup = @"([0-9a-fA-F]{1,4})";
        var ipv6pattern = string.Format(@"(?n)^({0}:){{7}}{0}$", hexgroup);
        var ipv6 = new Regex(ipv6pattern);

        foreach (var n in Enumerable.Range(0, int.Parse(Console.ReadLine()))) {
            var s = Console.ReadLine();

            if (ipv4.IsMatch(s))        Console.WriteLine("IPv4");
            else if (ipv6.IsMatch(s))   Console.WriteLine("IPv6");
            else                        Console.WriteLine("Neither");
        }
    }
}
