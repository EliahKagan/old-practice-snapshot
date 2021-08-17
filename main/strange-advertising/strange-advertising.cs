using static System.Console;

internal static class Solution {
    private static void Main()
    {
        const int start = 2;

        var sum = start;
        var cur = start;

        checked {
            for (var i = int.Parse(ReadLine())  - 1; i > 0; --i)
                sum += (cur = cur * 3 / 2);
        }

        WriteLine(sum);
    }
}
