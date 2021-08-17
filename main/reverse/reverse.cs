// reverse.cs - reverse a string, assuming no surrogate pairs

using System;
using System.Diagnostics.Contracts;
using System.Linq;
using System.Text;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class Program {
    private static string Backwards(string s)
    {
        Contract.Assert(s != null);

        var sb = new StringBuilder(s.Length);
        for (var i = s.Length - 1; i >= 0; --i) sb.Append(s[i]);
        return sb.ToString();
    }

    private static void Main(string[] args)
    {
        var s = string.Join(" ", args);
        var r = Backwards(s);

        Console.WriteLine("Got string:\n  {0}\n\nReversed:\n  {1}\n", s, r);

        if (r == new string(s.Reverse().ToArray()))
            Console.WriteLine("Good. Computed reverse appears correct.");
        else {
            Console.WriteLine("Oh no! Computed reverse appears incorrect.");
            Environment.ExitCode = 1;
        }
    }
}
