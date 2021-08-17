// euler17.cs  - Project Euler problem 17: Number letter counts

#define DEBUG

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.IO;
using System.Linq;
using System.Security;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class NumberWords {
#if TRUTH_JUSTICE_AND_THE_AMERICAN_WAY
    internal const string CentSep = " ";
#else
    internal const string CentSep = " and ";
#endif

    internal static IEnumerable<int> Range
    {
        get {
            return Enumerable.Range(1, 1000);
        }
    }

    internal static string Get(int n)
    {
        return names[n];
    }

    private static Dictionary<int, string> names = new Dictionary<int, string>{
        { 1, "one" },
        { 2, "two" },
        { 3, "three" },
        { 4, "four" },
        { 5, "five" },
        { 6, "six" },
        { 7, "seven" },
        { 8, "eight" },
        { 9, "nine" },
        { 10, "ten" },
        { 11, "eleven" },
        { 12, "twelve" },
        { 13, "thirteen" },
        { 14, "fourteen" },
        { 15, "fifteen" },
        { 16, "sixteen" },
        { 17, "seventeen" },
        { 18, "eighteen" },
        { 19, "nineteen" },
        { 20, "twenty" },
        { 30, "thirty" },
        { 40, "forty" },
        { 50, "fifty" },
        { 60, "sixty" },
        { 70, "seventy" },
        { 80, "eighty" },
        { 90, "ninety" },
        { 1000, "one thousand" }
    };

    static NumberWords()
    {
        for (var i = 20; i <= 90; i += 10) {
            for (var j = 1; j <= 9; ++j)
                names.Add(i + j, string.Format("{0}-{1}", names[i], names[j]));
        }

        for (var i = 1; i <= 9; ++i) {
            var h = i * 100;
            names.Add(h, names[i] + " hundred");

            for (var j = 1; j <= 99; ++j) {
                names.Add(h + j, string.Format("{0}{1}{2}",
                                               names[h], CentSep, names[j]));
            }
        }

        Contract.Assert(Range.All(names.ContainsKey));
    }
}

internal static class Program {
    private static bool can_color = true;

    private static ConsoleColor Color
    {
        set {
            if (can_color) {
                try {
                    Console.ForegroundColor = value;
                }
                catch (SecurityException)   { can_color = false; }
                catch (IOException)         { can_color = false; }
            }
        }
    }

    // Write a length value, colorized.
    private static void PutLength(int length, bool parens, bool newline)
    {
        if (parens) Console.Write('(');

        Color = ConsoleColor.Yellow;
        Console.Write(length);
        Color = ConsoleColor.Gray;

        if (parens) Console.Write(')');
        if (newline) Console.WriteLine();
    }

    // Write number out in English and the number of letters written.
    // Returns the number of letters written.
    private static int PutRecord(int value)
    {
        var name = NumberWords.Get(value);
        var length = name.Count(char.IsLetter);

        Console.Write("{0}  ", name);
        PutLength(length, true, true);

        return length;
    }

    private static void Main()
    {
        var total = NumberWords.Range.Sum(PutRecord);
        Console.Write("{0}Total letters: ", Environment.NewLine);
        PutLength(total, false, true);
    }
}
