using System;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    private static unsafe void Main()
    {
        var n = int.Parse(Console.ReadLine());
        var a = stackalloc int[n + 1];
        a[0] = int.MinValue;

        for (var i = 0; i != n; ) {
            var e = int.Parse(Console.ReadLine());
            var k = i + 1;
            for (var j = i; e < a[j];) a[k--] = a[j--];
            a[k] = e;

            var mid = ++i / 2;

            if (i % 2 == 0) {
                var m = a[mid] + a[mid + 1];
                Console.WriteLine("{0}.{1}", m / 2, (m % 2 == 0 ? '0' : '5'));
            }
            else Console.WriteLine("{0}.0", a[mid + 1]);
        }
    }
}
