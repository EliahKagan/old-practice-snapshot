using System.Runtime.InteropServices;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    [DllImport("msvcrt.dll")]
    private static extern int printf(string format, __arglist);

    [DllImport("msvcrt.dll")]
    private static extern int scanf(string format, __arglist);

    private static unsafe void Main()
    {
        int x, y;
        scanf("%d%d", __arglist(&x, &y));
        printf("%d\n", __arglist(x + y));
    }
}
