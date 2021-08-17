// Let's see if "Hash Tables: Ransom Note" allows the kidnapper to photocopy
// words from the magazine (i.e., use a word more times than it appears).

using static System.Array;
using static System.Console;

[assembly: System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class Solution {
    private static string[] ReadWords() => ReadLine().Split(' ');

    private static void Main()
    {
        ReadLine(); // don't need m, n

        var dic = ReadWords();
        Sort(dic);

        var yes = TrueForAll(ReadWords(), w => BinarySearch(dic, w) >= 0);
        WriteLine(yes ? "Yes" : "No");
    }
}
