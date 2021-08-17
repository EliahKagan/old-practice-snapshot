#define ROBUST_POW

using System;
using System.Runtime.CompilerServices;

[assembly: System.Reflection.AssemblyVersion("0.1.0.0")]

internal struct Matrix2x2 {
    public const long Mod = 1000000007L;

    public static readonly Matrix2x2 Zero = new Matrix2x2();
    public static readonly Matrix2x2 Identity = new Matrix2x2(1, 0, 0, 1);
    public static readonly Matrix2x2 FibGen = new Matrix2x2(1, 1, 1, 0);

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static Matrix2x2 operator +(Matrix2x2 a, Matrix2x2 b)
    {
        return new Matrix2x2((a.e11 + b.e11) % Mod, (a.e12 + b.e12) % Mod,
                             (a.e21 + b.e21) % Mod, (a.e22 + b.e22) % Mod);
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static Matrix2x2 operator -(Matrix2x2 a, Matrix2x2 b)
    {
        return new Matrix2x2((a.e11 - b.e11) % Mod, (a.e12 - b.e12) % Mod,
                             (a.e21 - b.e21) % Mod, (a.e22 - b.e22) % Mod);
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static Matrix2x2 operator *(Matrix2x2 a, Matrix2x2 b)
    {
        return new Matrix2x2((a.e11 * b.e11 + a.e12 * b.e21) % Mod,
                             (a.e11 * b.e12 + a.e12 * b.e22) % Mod,
                             (a.e21 * b.e11 + a.e22 * b.e21) % Mod,
                             (a.e21 * b.e12 + a.e22 * b.e22) % Mod);
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static Vector2 operator *(Matrix2x2 a, Vector2 v)
    {
        return new Vector2((a.e11 * v[1] + a.e12 * v[2]) % Mod,
                           (a.e21 * v[1] + a.e22 * v[2]) % Mod);
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static Matrix2x2 operator *(long k, Matrix2x2 a)
    {
        return new Matrix2x2((k * a.e11) % Mod, (k * a.e12) % Mod,
                             (k * a.e21) % Mod, (k * a.e22) % Mod);
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static Matrix2x2 operator *(Matrix2x2 a, long k)
    {
        return k * a;
    }

    public static Matrix2x2 Pow(Matrix2x2 a, int p)
    {
#if ROBUST_POW
        if (p < 2) {
            switch (p) {
                case 1:     return a;
                case 0:     return Identity;
                default:    throw new ArgumentOutOfRangeException("p");
            }
        }
#else
        if (p == 1) return a;
#endif

        var b = Pow(a, p / 2);
        b *= b;
        if (p % 2 != 0) b *= a;

        return b;
    }

#if TESTS
    public static void TestPow()
    {
#if ROBUST_POW
        var i = 0;
#else
        var i = 1;
#endif
        for (; i <= 20; ++i)
            Console.WriteLine(Matrix2x2.Pow(Matrix2x2.FibGen, i));
    }

    public static void TestFib()
    {
        for (var n = 0; n <= 20; ++n)
            Console.WriteLine("{0,2}:  {1}", n, Pow(FibGen, n) * Vector2.I);
    }
#endif // ! TESTS

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public Matrix2x2(long e11, long e12, long e21, long e22)
    {
        this.e11 = e11;
        this.e12 = e12;
        this.e21 = e21;
        this.e22 = e22;
    }

    public long this[int i, int j]
    {
        get {
            switch (i) {
            case 1:
                switch (j) {
                    case 1:     return e11;
                    case 2:     return e12;
                    default:    throw new ArgumentOutOfRangeException("j");
                }

            case 2:
                switch (j) {
                    case 1:     return e21;
                    case 2:     return e22;
                    default:    throw new ArgumentOutOfRangeException("j");
                }

            default:            throw new ArgumentOutOfRangeException("i");
            }
        }
    }

    public override string ToString()
    {
        return string.Format("(({0}, {1}), ({2}, {3}))",
                             e11, e12, e21, e22);
    }

    private readonly long e11, e12, e21, e22;
}

internal struct Vector2 {
    public const long Mod = Matrix2x2.Mod;

    public static readonly Vector2 Zero = new Vector2();
    public static readonly Vector2 I = new Vector2(1, 0);
    public static readonly Vector2 J = new Vector2(0, 1);

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static Vector2 operator +(Vector2 u, Vector2 v)
    {
        return new Vector2((u.e1 + v.e1) % Mod, (u.e2 + v.e2) % Mod);
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static Vector2 operator -(Vector2 u, Vector2 v)
    {
        return new Vector2((u.e1 - v.e1) % Mod, (u.e2 - v.e2) % Mod);
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static Vector2 operator *(long k, Vector2 v)
    {
        return new Vector2((k * v.e1) % Mod, (k * v.e2) % Mod);
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static Vector2 operator *(Vector2 v, long k)
    {
        return k * v;
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public Vector2(long e1, long e2)
    {
        this.e1 = e1;
        this.e2 = e2;
    }

    public long this[int i]
    {
        get {
            switch (i) {
                case 1:     return e1;
                case 2:     return e2;
                default:    throw new ArgumentOutOfRangeException("i");
            }
        }
    }

    public override string ToString()
    {
        return string.Format("({0}, {1})", e1, e2);
    }

    private readonly long e1, e2;
}

internal static class Solution {
    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    private static long Fib(long a, long b, int n)
    {
        return (Matrix2x2.Pow(Matrix2x2.FibGen, n - 1) * new Vector2(b, a))[1];
    }

    private static void Main()
    {
        for (var t = int.Parse(Console.ReadLine()); t > 0; --t) {
            var record = Console.ReadLine().Split(' ');

            var a = long.Parse(record[0]);
            var b = long.Parse(record[1]);
            var n = int.Parse(record[2]);

            Console.WriteLine(Fib(a, b, n));
        }
    }
}
