using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

internal sealed class BitSet : IEnumerable<int> {
    private readonly ulong[] _bits;

    public BitSet(int capacity, bool fill = false)
    {
        var length = capacity / 64;
        var tail = capacity % 64;
        if (tail != 0) ++length;
        var excess = 64 - tail;

        if (fill) {
            _bits = Enumerable.Repeat(ulong.MaxValue, length).ToArray();
            _bits[length - 1] >>= excess;
        }
        else _bits = new ulong[length];
    }

    public int Capacity => _bits.Length * 64;

    public bool Contains(int value)
        => (_bits[value >> 6] & 1uL << (value & 63)) != 0;

    public void Add(int value)
        => _bits[value >> 6] |= 1uL << (value & 63);

    public void Remove(int value)
        => _bits[value >> 6] &= ~(1uL << (value & 63));

    public IEnumerator<int> GetEnumerator()
    {
        for (var i = 0; i != _bits.Length; ++i) {
            if (_bits[i] == 0uL) continue;

            var ho = i << 6;

            for (var jmin = 0; jmin != 64; jmin += 8) {
                var b = _bits[i] & 0xFFuL << jmin;
                if (b == 0uL) continue;

                var jstop = jmin + 8;
                for (var j = jmin; j != jstop; ++j)
                    if ((b & 1uL << j) != 0uL) yield return ho | j;
            }
        }
    }

    IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();
}

internal sealed class Primes {
    private static BitSet RawSieve(int n)
    {
        var len = (n + 1) / 2;
        var s = new BitSet(len, true);

        var istop = (int)Math.Sqrt(n) / 2 + 1;
        for (var i = 1; i != istop; ++i) {
            if (s.Contains(i)) {
                var jstep = i * 2 + 1;
                for (var j = (i + 1) * i * 2; j < len; j += jstep) s.Remove(j);
            }
        }

        return s;
    }

    private static IEnumerable<int> Sieve(int n)
    {
        yield return 2;
        foreach (var k in RawSieve(n).Skip(1)) yield return k * 2 + 1;
    }

    private readonly int[] _elems;

    public Primes(int n)
    {
        _elems = Sieve(n).ToArray();
    }

    public IEnumerable<int> Range(int lower_bound, int upper_bound)
    {
        var i = Array.BinarySearch(_elems, lower_bound);
        if (i < 0) i = ~i;

        var j = Array.BinarySearch(_elems, i, _elems.Length - i, upper_bound);
        j = (j < 0 ? ~j : j + 1);

        while (i != j) yield return _elems[i++];
    }
}

internal static class UnitTest {
    private static void Main()
    {
        var primes = new Primes(100000000);

        for (var t = int.Parse(Console.ReadLine()); t > 0; --t) {
            var bounds = Console.ReadLine().Split('-');

            var range = primes.Range(int.Parse(bounds[0]),
                                     int.Parse(bounds[1]));

            Console.WriteLine(string.Join(" ", range));
        }
    }
}
