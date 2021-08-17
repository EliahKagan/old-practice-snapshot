using System;
using System.IO;
using System.Text.RegularExpressions;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Program {
    private static void Main(String[] args)
    {
        foreach (var path in args) {
            try {
                var lc = 0L;
                var wc = 0L;

                foreach (var line in File.ReadLines(path)) {
                    ++lc;
                    wc += WordPattern.Matches(line).Count;
                }

                Console.WriteLine("{0}: {1}, {2}", path, lc.WithUnit("line"),
                                                         wc.WithUnit("word"));
            }
            catch (IOException e) {
                var name = Environment.GetCommandLineArgs()[0];
                Console.Error.WriteLine($"{name}: error: {path}: {e.Message}");
                Environment.ExitCode = 1;
            }
        }
    }

    /// <summary>Makes regular plurals.</summary>
    private static string WithUnit(this long self, string unit)
        => $"{self} {unit}{(self == 1 ? "" : "s")}";

    private static readonly Regex WordPattern = new Regex(@"\S+");
}
