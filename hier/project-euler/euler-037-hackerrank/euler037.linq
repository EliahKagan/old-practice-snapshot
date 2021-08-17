<Query Kind="Program" />

internal static class EnumerableEx {
    internal static IEnumerable<int> IntersectSorted(
            this IEnumerable<int> self, IEnumerable<int> other)
    {
        using (var en = other.GetEnumerator()) {
            if (!en.MoveNext()) yield break;

            foreach (var x in self) {
                while (en.Current < x)
                    if (!en.MoveNext()) yield break;

                if (en.Current == x) yield return x;
            }
        }
    }
}

internal static class Primes {
    private static IEnumerable<int> Sieve(int n) // yields primes up to n
    {
        var a = new bool[n + 1]; // false means not marked as composite
    
        var imax = Convert.ToInt32(Math.Floor(Math.Sqrt(n)));
        for (var i = 3; i <= imax; i += 2) {
            if (!a[i]) {
                var jstep = i * 2;
                for (var j = i * i; j <= n; j += jstep) a[j] = true;
            }
        }
    
        yield return 2;
        for (var k = 3; k <= n; k += 2)
            if (!a[k]) yield return k;
    }

    internal static int[] To(int n) => Sieve(n).ToArray(); // primes to n
}

internal static class Arithmetic {
    private const int Billion = 1000000000; // highest power of 10 int can fit

    private static readonly int[] PowersOf10 = ComputePowersOf10().ToArray();

    private static IEnumerable<int> ComputePowersOf10()
    {
        for (var i = 1; ; i *= 10) {
            yield return i;
            if (i == Billion) yield break;
        }
    }

    // Returns the highest power of 10 strictly less than n. Assumes n > 1.
    internal static int PrevPowerOf10(this int n)
    {
        var i = Array.BinarySearch(PowersOf10, n);
        return PowersOf10[(i < 0 ? ~i : i) - 1];
    }
}

internal static class TruncationArithmetic {
    private static List<int> Reducibles(this int[] seq,
            Func<int, bool> seeder, Func<int, int> reducer)
    {
        var ret = new List<int>(seq.Length);
        ret.AddRange(seq.TakeWhile(seeder));

        foreach (var n in seq.Skip(ret.Count))
            if (ret.BinarySearch(reducer(n)) >= 0) ret.Add(n);

        return ret;
    }

    // Returns elements of a whose left and right trunctions are all also in a.
    // a must be strictly increasing (sorted and unique) and everywhere > 0.
    internal static IEnumerable<int> Truncateables(this int[] seq)
    {
        var left = seq.Reducibles(n => n < 10, n => n / 10);
        var right = seq.Reducibles(n => n < 10, n => n % n.PrevPowerOf10());
        return left.IntersectSorted(right);
    }
}

internal static class Solution {
    private static void Main()
    {
        const int max = 1000000;
        Primes.To(max).Truncateables().SkipWhile(p => p < 10).Dump();
    }
}
