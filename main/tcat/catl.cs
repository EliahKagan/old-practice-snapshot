// catl.cs - simple line-by-line cat program

using System;
using System.Diagnostics.Contracts;
using System.IO;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class Diag { // diagnostic messages and exit status
    internal static void Note(string format, params object[] args)
    {
        Message("note", format, args);
    }

    internal static void Warn(string format, params object[] args)
    {
        Message("warning", format, args);
    }

    internal static void Error(string format, params object[] args)
    {
        Message("error", format, args);
        Environment.ExitCode = 1;
    }

    internal static void Fatal(string format, params object[] args)
    {
        Error(format, args);
        Die();
    }

    private static string s_prefix = null;

    private static string GetAppName()
    {
        try { return Environment.GetCommandLineArgs()[0]; }
        catch (ArgumentOutOfRangeException) {
            throw new NotSupportedException();
        }
    }

    private static string Prefix
    {
        get {
            if (s_prefix == null) {
                try { s_prefix = GetAppName() + ": "; }
                catch (NotSupportedException) { s_prefix = ""; }
            }

            return s_prefix;
        }
    }

    private static void Message(string label, string format,
                                params object[] args)
    {
        Contract.Assert(label != null && format != null);

        Console.Error.WriteLine("{0}{1}: {2}", Prefix, label,
                                string.Format(format, args));
    }

    private static void Die()
    {
        Environment.Exit(Environment.ExitCode);
    }
}

internal static class CatL {
    private static void WriteLine(string value)
    {
        Contract.Assert(value != null);

        try { Console.WriteLine(value); }
        catch (IOException e) {
            Diag.Fatal("can't write standard output: {0}", e.Message);
        }
    }

    private static string InNameFromPath(string path)
    {
        return path == null ? string.Format("\"{0}\"", path)
                            : "standard input";
    }

    private static void Cat(TextReader reader, string path)
    {
        Contract.Assert(reader != null);

        try {
            for (string s; (s = reader.ReadLine()) != null; ) WriteLine(s);
        }
        catch (IOException e) {
            Diag.Error("can't read {0}: {1}", InNameFromPath(path), e.Message);
        }
        catch (OutOfMemoryException) {
            Diag.Error("can't read {0}: out of memory "
                        + "(possible very long line)", InNameFromPath(path));
        }
        catch (ArgumentOutOfRangeException) {
            Diag.Error("can't read {0}: line length exceeds {1}",
                       InNameFromPath(path), int.MaxValue);
        }
    }

    private static void BadPathCharError(string path)
    {
        Contract.Assert(path != null);

        var chs = Path.GetInvalidPathChars();
        var i = path.IndexOfAny(chs);

        if (i == -1) {
            Diag.Error("can't open \"{0}\": bad path (invalid character)",
                       path);
        } else {
            Diag.Error("can't open \"{0}\": invalid character \"{1}\"",
                       path, chs[i]);
        }
    }

    private static void BadPathError(string path)
    {
        Contract.Assert(path != null);

        if (path.Length == 0)
            Diag.Error("can't open \"\": empty string is invalid path");
        else if (path.TrimStart().Length == 0) {
            Diag.Error("can't open \"{0}\": system prohibits whitespace path",
                       path);
        }
        else BadPathCharError(path);
    }

    private static void LongPathError(string path)
    {
        Contract.Assert(path != null);

        Diag.Error("can't open \"{0}\": path or filename too long", path);
        
        switch (Environment.OSVersion.Platform) {
        case PlatformID.Win32NT: case PlatformID.WinCE: case PlatformID.Xbox:
            Diag.Note("use \"\\\\.\\\" form of "
                        + "filenames >= 260, paths >= 248 chars");
            break;
        }
    }

    private static void UnauthorizedPathError(string path)
    {
        Contract.Assert(path != null);

        if (Directory.Exists(path))
            Diag.Error("can't open \"{0}\": is a directory", path);
        else
            Diag.Error("can't open \"{0}\": access denied", path);
    }

    private static void CatFile(string path)
    {
        Contract.Assert(path != null);
        
        try {
            using (var f = File.OpenRead(path))
                using (var r = new StreamReader(f, true)) Cat(r, path);
        }
        catch (ArgumentException) { BadPathError(path); }
        catch (PathTooLongException) { LongPathError(path); }
        catch (DirectoryNotFoundException) {
            Diag.Error("can't open \"{0}\": directory not found", path);
        }
        catch (UnauthorizedAccessException) { UnauthorizedPathError(path); }
        catch (FileNotFoundException) {
            Diag.Error("can't open \"{0}\": file not found", path);
        }
        catch (NotSupportedException) {
            Diag.Error("can't open \"{0}\": bad path (invalid format)", path);
        }
        catch (IOException e) {
            Diag.Error("can't open \"{0}\": {1}", path, e.Message);
        }
    }
    
    private static void CatStdin()
    {
        Cat(Console.In, null);
    }

    private static void CatArg(string arg, ref bool no_opts)
    {
        Contract.Assert(arg != null);

        if (no_opts)
            CatFile(arg);
        else if (arg.Length == 0)
            Diag.Warn("ignoring empty (zero-length) argument");
        else if (arg == "--")
            no_opts = true;
        else if (arg == "-")
            CatStdin();
        else
            CatFile(arg);
    }

    private static void Main(string[] args)
    {
        if (args.Length == 0) CatStdin();
        else {
            var no_opts = false;
            foreach (var arg in args) CatArg(arg, ref no_opts);
        }
    }
}
