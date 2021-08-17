using static System.Console;

internal static class Solution {
    private static void Main()
    {
        var n = int.Parse(ReadLine());
        var b = ReadLine().Trim();

        var count = 0;

        var stop = n - 3;
        for (var i = 0; i <= stop; ) {
            if (b[i] == '0' && b[i + 1] == '1' && b[i + 2] == '0') {
                ++count;
                i += 3;
            }
            else ++i;
        }

        WriteLine(count);
    }
}
