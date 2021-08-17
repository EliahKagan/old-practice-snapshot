using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

[assembly: System.Reflection.AssemblyVersion("1.0.3.0")]

internal static class Buffer {
    private const int Capacity = 1_000_000; // maximum text length accommodated

    private static StringBuilder Buf = new StringBuilder(Capacity, Capacity);

    internal static void Append(string text) => Buf.Append(text);

    internal static void Erase(int length) => Buf.Length -= length;

    internal static string RightSubstring(int length)
            => Buf.ToString().Substring(Buf.Length - length);

    internal static char Get(int i) => Buf[i - 1];
}

internal static class Editor {
    private const int Capacity = 1_000_000; // maximum height of undo stack

    private static Stack<Action> Undos = new Stack<Action>(Capacity);

    internal static void Append(string text)
    {
        var length = text.Length;
        Buffer.Append(text);
        Undos.Push(() => Buffer.Erase(length));
    }

    internal static void Erase(int length)
    {
        var text = Buffer.RightSubstring(length);
        Buffer.Erase(length);
        Undos.Push(() => Buffer.Append(text));
    }

    internal static void Print(int i) => Console.WriteLine(Buffer.Get(i));

    internal static void Undo() => Undos.Pop()();
}

internal static class Queries {
    private static Action Interpret(string[] tok)
    {
        switch (int.Parse(tok[0])) {
            case 1:     return () => Editor.Append(tok[1]);
            case 2:     return () => Editor.Erase(int.Parse(tok[1]));
            case 3:     return () => Editor.Print(int.Parse(tok[1]));
            case 4:     return Editor.Undo;
            default:    throw new ArgumentException("unrecognized query kind");
        }
    }

    private static IEnumerable<string> ReadLines()
    {
        for (string line; (line = Console.ReadLine()) != null;)
            yield return line;
    }

    internal static IEnumerable<Action> Get()
            => ReadLines().Skip(1) // ignore apparently unreliable Q value
                          .Select(line => Interpret(line.Split(' ')));
}

internal static class Solution {
    private static void Main()
    {
        foreach (var query in Queries.Get()) query();
    }
}
