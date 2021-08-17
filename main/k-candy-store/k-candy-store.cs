using System;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Arith {
    internal static int[,] ComputeBinomialCoefficientsModulo(int size, int mod)
    {
        if (size < 2) size = 2;

        var c = new int[size, size];
        c[0, 0] = c[1, 0] = c[1, 1] = 1;

        for (var n = 2; n != size; ++n) {
            c[n, 0] = c[n, n] = 1;

            for (var r = 1; r != n; ++r)
                c[n, r] = (c[n - 1, r - 1] + c[n - 1, r]) % mod;
        }

        return c;
    }
}

internal struct Pair<T> {
    public T X, Y;
}

internal static class Solution {
    private static int GetValue() => int.Parse(Console.ReadLine());

    private static void Main()
    {
        const int mod = 1000000000;

        var a = new Pair<int>[GetValue()];
        var max = 1;

        for (var i = 0; i != a.Length; ++i) {
            a[i].X = GetValue();
            a[i].Y = GetValue();
            a[i].X += a[i].Y - 1;
            if (max < a[i].X) max = a[i].X;
        }

        var c = Arith.ComputeBinomialCoefficientsModulo(max + 1, mod);
        Array.ForEach(a, p => Console.WriteLine(c[p.X, p.Y]));
    }
}
