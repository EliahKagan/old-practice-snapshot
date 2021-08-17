<Query Kind="Program">
  <Namespace>System.Diagnostics.Contracts</Namespace>
</Query>

internal static class LexicographicAlgorithms {
    internal static char[] GetAlphabet(this string text, int assert_length)
    {
        var s = text.Trim().ToCharArray();
        Contract.Assert(s.Length == assert_length);
        Array.Sort(s);
        return s;
    }

    private static IEnumerable<char> GetLetters(this char[] alphabet, int mask)
            => from i in Enumerable.Range(0, alphabet.Length)
               where (mask >> i & 1) != 0
               select alphabet[i];
    
    private static string GetWord(this char[] alphabet, int mask)
            => new string(alphabet.GetLetters(mask).ToArray());
    
    private static IEnumerable<string> GetAllWords(this char[] alphabet)
            => from i in Enumerable.Range(1, (1 << alphabet.Length) - 1)
               select alphabet.GetWord(i);
    
    internal static string[] GetSortedWordArray(this char[] alphabet)
    {
        var a = alphabet.GetAllWords().ToArray();
        Array.Sort(a);
        return a;
    }
}

internal static class Solution {
    private static int ReadValue() => int.Parse(Console.ReadLine());

    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, ReadValue())) {
            var n = ReadValue();
            var a = Console.ReadLine().GetAlphabet(n).GetSortedWordArray();
            Console.WriteLine(string.Join(" ", a));
        }
    }
}