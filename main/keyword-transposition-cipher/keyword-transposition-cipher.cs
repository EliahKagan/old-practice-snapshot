#define DEBUG

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;
using static System.Console;

internal static class Solution {
    private const int AlphabetLen = 26;

    private static IEnumerable<char> Alphabet()
            => Enumerable.Range('A', AlphabetLen).Select(Convert.ToChar);

    private static bool IsAlphabet(char c) => 'A' <= c && c <= 'Z';

    private static char[] ReduceWord(string keyword, out int n)
    {
        var word = keyword.Trim().ToUpperInvariant().Distinct().ToArray();
        Contract.Assert(Array.TrueForAll(word, IsAlphabet));

        n = word.Length;
        Contract.Assert(n != 0, "can't use zero-length keyword");

        return word;
    }

    private static char[][] GetGrid(string keyword)
    {
        int n;
        var word = ReduceWord(keyword, out n);
        var m = AlphabetLen / n + Math.Sign(AlphabetLen % n);
        Contract.Assert((m - 1) * n < AlphabetLen && AlphabetLen <= m * n);

        var grid = Array.ConvertAll(word, c => { // column-major representation
            var col = new char[m];
            col[0] = c;
            return col;
        });

        var k = n; // indexes grid in row-major order
        foreach (var c in Alphabet().Except(word)) {
            grid[k % n][k / n] = c;
            ++k;
        }

        return grid;
    }

    private static string GetKey(string keyword)
    {
        var grid = GetGrid(keyword);
        Array.Sort(grid, (u, v) => u[0] - v[0]);

        var cols = Array.ConvertAll(grid, col => new string(col).TrimEnd('\0'));
        var key = string.Concat(cols);
        Contract.Assert(key.Length == AlphabetLen);

        return key;
    }

    private static char[] Decrypt(this string key, string msg)
    {
        return msg.TrimEnd().ToUpperInvariant()
                .Select(c => IsAlphabet(c) ? (char)('A' + key.IndexOf(c)) : c)
                .ToArray();
    }

    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, int.Parse(ReadLine())))
            WriteLine(GetKey(ReadLine()).Decrypt(ReadLine()));
    }
}
