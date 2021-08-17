using System;
using System.Linq;
using System.Text;

[assembly: System.Reflection.AssemblyVersion("1.2.0.0")]

internal static class Solution {
    private static unsafe void Main()
    {
        var sb = new StringBuilder();

        var n = int.Parse(Console.ReadLine());
        var a = stackalloc int[n + 1];
        a[0] = int.MinValue;
        
        var i = 0;
        foreach (var e in Console.In.ReadToEnd().Split('\n')
                                                .Take(n)
                                                .Select(int.Parse)) {
            var k = i + 1;
            for (var j = i; e < a[j];) a[k--] = a[j--];
            a[k] = e;

            var mid = ++i / 2;

            if (i % 2 == 0) {
                var m = a[mid] + a[mid + 1];
                sb.AppendLine($"{m / 2}.{(m % 2 == 0 ? '0' : '5')}");
            }
            else sb.AppendLine($"{a[mid + 1]}.0");
        }

        Console.Write(sb.ToString());
    }
}
