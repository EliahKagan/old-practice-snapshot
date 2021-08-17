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

internal static class UnitTest {
    private static void Main()
    {
        const int range = 1000000, step = 3000;

        var s = new BitSet(range);
        Console.WriteLine($"Capacity: {s.Capacity}");

        for (var i = 0; i < range; i += step)
            if (i % step == 0) s.Add(i);

        Console.WriteLine(string.Join(" ", s));

        /*
        var s = new BitSet(1000, true);
        Console.WriteLine($"Capacity: {s.Capacity}");

        for (var i = 0; i != 1000; ++i)
            if (i % 3 != 0) s.Remove(i);

        Console.WriteLine(string.Join(" ", s));
        */
    }
}
