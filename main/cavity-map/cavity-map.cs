using System;

internal static class Solution {
    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());
        
        if (n <= 1) { // given problem constraints, this means n == 1
            Console.WriteLine(Console.ReadLine());
            return;
        }

        var a = new char[n][];
        for (var i = 0; i != n; ++i)
            a[i] = Console.ReadLine().ToCharArray();

        var m = n - 1;
        for (var i = 1; i != m; ++i) {
            for (var j = 1; j != m; ++j) {
                var c = a[i][j];

                if (a[i][j - 1] < c && a[i][j + 1] < c
                                    && a[i - 1][j] < c && a[i + 1][j] < c)
                    a[i][j] = 'X';
            }
        }

        foreach (var row in a) Console.WriteLine(row);
    }
}
