using System;

internal static class Solution {
    private static void GetParams(out int x1, out int v1, out int x2, out int v2)
    {
        var a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

        x1 = a[0];
        v1 = a[1];
        x2 = a[2];
        v2 = a[3];
    }

    private static bool KangaroosMeetAtTick(int x1, int v1, int x2, int v2)
    {
        var dx = x2 - x1;
        if (dx == 0) return true; // already together

        var neg_dv = v1 - v2;
        if (neg_dv == 0) return false; // never change distance

        if (Math.Sign(dx) != Math.Sign(neg_dv)) return false; // widening gap

        return dx % neg_dv == 0; // cross at a tick (so are both on ground)
    }

    private static void Main()
    {
        int x1, v1, x2, v2;
        GetParams(out x1, out v1, out x2, out v2);
        Console.WriteLine(KangaroosMeetAtTick(x1, v1, x2, v2) ? "YES" : "NO");
    }
}
