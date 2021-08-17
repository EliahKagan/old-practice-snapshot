using System.Collections.Generic;
using static System.Console;

[assembly: System.Reflection.AssemblyVersion("2.0.0.0")]

internal static class Solution {
    private static readonly IReadOnlyDictionary<char, char> Groupers =
        new Dictionary<char, char> { { '(', ')' }, { '[', ']' }, { '{', '}' } };

    private static readonly ISet<char> Closers =
        new HashSet<char>(Groupers.Values); // warning: contents modifiable

    private static bool IsBalanced(this string str)
    {
        const char start_mark = '\0'; // any non-closer works here

        var closer_stack = new Stack<char>();
        closer_stack.Push(start_mark);

        foreach (var c in str) {
            if (Groupers.ContainsKey(c))
                closer_stack.Push(Groupers[c]);
            else if (Closers.Contains(c) && closer_stack.Pop() != c)
                return false;
        }

        // only balanced if all are closed
        return closer_stack.Pop() == start_mark;
    }

    private static void Main()
    {
        for (var t = int.Parse(ReadLine()); t > 0; --t)
            WriteLine(ReadLine().IsBalanced() ? "YES" : "NO");
    }
}
