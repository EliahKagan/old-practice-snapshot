using System;
using System.Collections.Generic;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    private static bool IsBalanced(this string str)
    {
        const char start_mark = '\0'; // any char but ')', ']', '}' works here

        var closers = new Stack<char>();
        closers.Push(start_mark);

        foreach (var c in str) {
            switch (c) {
            case '(':
                closers.Push(')');
                continue;

            case '[':
                closers.Push(']');
                continue;

            case '{':
                closers.Push('}');
                continue;

            case ')':
            case ']':
            case '}':
                if (closers.Pop() != c) return false;
                continue;

            default:
                continue; // ignore non-grouping characters
            }
        }

        return closers.Pop() == start_mark; // only balanced if all are closed
    }

    private static void Main()
    {
        for (var t = int.Parse(Console.ReadLine()); t > 0; --t)
            Console.WriteLine(Console.ReadLine().IsBalanced() ? "YES" : "NO");
    }
}
