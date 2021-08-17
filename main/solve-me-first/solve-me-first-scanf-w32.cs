using System.Runtime.InteropServices;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    [DllImport("msvcrt.dll")]
    private static extern int printf(string format, __arglist);

    [DllImport("msvcrt.dll")]
    private static extern int scanf(string format, __arglist);

    private static void Main()
    {
        var x = 0;
        var y = 0;
        scanf("%d%d", __arglist(ref x, ref y));
        printf("%d", __arglist(x + y));
    }
}
