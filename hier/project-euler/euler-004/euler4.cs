// euler4.cs - Project Euler problem 4: Largest palindrome product

using System;
using System.Globalization;
using System.Linq;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class Program {
    private static bool IsPalindrome(int n)
    {
        var s = n.ToString(CultureInfo.InvariantCulture);
        return s == new string(s.Reverse().ToArray());
    }

    private const int Min = 100, Max = 999;

    private static int Main()
    {
        for (var i = Max; i >= Min; --i) {
            for (var j = i; j >= Min; --j) {
                var n = j * i;
                if (IsPalindrome(n)) {
                    Console.WriteLine("{0} * {1} = {2}", j, i, n);
                    return 0;
                }
            }
        }

        return 1;
    }
}
