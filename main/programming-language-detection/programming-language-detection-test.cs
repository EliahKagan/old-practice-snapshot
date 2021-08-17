// programming-language-detection-test.cs - local testsuite to guess if a
//   https://www.hackerrank.com/challenges/programming-language-detection/forum
//   "solution" is likely to succeed against likely, non-challenging test cases

#define DEBUG

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.IO;
using System.Linq;
using System.Security;
using System.Text;
using System.Text.RegularExpressions;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

[Serializable]
internal sealed class UnreachableException : NotSupportedException { }

internal static enum Status { Passed, Failed, Error }; // keep in this order

internal static class Program {
    const string Delimiter = "@@@@"; // appears between test cases in a file
    private static readonly string[] DelimiterArray = new[] { Delimiter };
    private static readonly Regex DelimiterRegex
            = new Regex(string.Format(@"^{0}\s*$", Delimiter));

    private static readonly string Name, MyName;

    static Program()
    {
        const var my_suffix = "-test";

        try {
            Name = Regex.Matches(Environment.GetCommandLineArgs()[0],
                                 string.Format(@"^[^/{0}]+(?={1}(?:\.exe)?$)",
                                               Path.PathSeparator, my_suffix))
                        .Cast<Match>().Single();

            MyName = Name + my_suffix;
            return;
        }
        catch (InvalidOperationException) { // from .Single()
            Error("this utility must be named like *-test or *-test.exe");
        }
        catch (NotSupportedException) { }
        catch (ArgumentOutOfRangeException) { }

        Error("can't retrieve command-line args to determine own name");
    }

    private static void Quit(Status status)
    {
        Environment.Exit((int)status);
    }

    private static void Error(string format, params string[] args)
    {
        Contract.Assert(format != null && args != null);

        Console.Error.WriteLine("{0}{1}error: {2}", MyName,
                                (MyName == null ? string.Empty : ": "),
                                string.Format(format, args));

        Quit(Status.Error);
    }

    private static void GetTests(string lang)
    {
        Contract.Assert(lang != null);

        var path = lang + "examples.txt";
        var tests = new List<string>();
        var buf = new StringBuilder();

        try {
            foreach (var line in File.ReadLines(path).Concat(DelimiterArray)) {
                if (DelimiterRegex.IsMatch(line)) {
                    tests.Add(buf.ToString());
                    buf.Clear();
                }
                else buf.AppendLine(line);
            }

            return tests;
        }
        catch (FileNotFoundException) {
            Error("\"{0}\" not found: is \"{1}\" spelled right?", path, lang);
        }
        catch (IOException e) { }
        catch (ArgumentException e) { }
        catch (SecurityException e) { }
        catch (UnauthorizedAccessException e) { }

        Error("can't open/read \"{0}\": {1}", path, e.Message);
        throw new UnreachableException();
    }

    private static void TestLanguage(string lang)
    {
        Contract.Assert(lang != null);

        var tests = GetTests(lang);
        //

        Environment.
    }

    private static void Main(string[] args)
    {
        var tested = false;

        foreach (var lang in args.Select(a => a.Trim().ToLower()).Distinct()) {
            TestLanguage(lang);
            tested = true;
        }

        if (!tested) {
            foreach (var lang in new[] { "java", "c", "python" })
                TestLanguage(lang);
        }

        Console.WriteLine("All tests passed.");
    }
}
