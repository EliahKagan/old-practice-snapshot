// esrever.cs - super serious, professional-quality string reverser
//     (correctly handles UTF-16 surrogate pairs, so is not limited to the BMP)
//
// To build:  csc /r:Microsoft.VisualBasic.dll esrever.cs  (or "mcs ...")

using System;
using System.IO;
using Microsoft.VisualBasic; // for Strings class

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

internal class UnreachableException : NotSupportedException { }

internal static class Esrever {
    private static void Die(string format, params object[] args)
    {
        Console.Error.WriteLine("{0}: error: {1}",
                                Environment.GetCommandLineArgs()[0],
                                string.Format(format, args));
        Environment.Exit(1);
    }

    private static string ReadLine()
    {
        try {
            return Console.ReadLine();
        }
        catch (IOException e) {
            Die("can't read stdin: {0}", e.Message);
        }
        catch (OutOfMemoryException) {
            Die("out of memory (very long line?)");
        }
        catch (ArgumentOutOfRangeException) {
            Die("line too long (over {0} UTF-16 code points)", int.MaxValue);
        }

        throw new UnreachableException();
    }

    private static void WriteLine(string s)
    {
        try {
            Console.WriteLine(s);
        }
        catch (IOException e) {
            Die("can't write stdout: {0}", e.Message);
        }
    }

    private static T QuitOnNull<T>(T x) where T : class
    {
        if (x == null) Environment.Exit(Environment.ExitCode);
        return x;
    }

    private static void Main()
    {
        for (; ; ) WriteLine(Strings.StrReverse(QuitOnNull(ReadLine())));
    }
}
