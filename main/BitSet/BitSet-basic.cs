using System;
using System.Collections.Generic;
using System.Linq;

internal sealed class BitSet {
    private readonly ulong[] _bits;

    public BitSet(int capacity, bool fill = false)
    {
        var length = capacity / 64;
        if (capacity % 64 != 0) ++length;

        _bits = (fill ? Enumerable.Repeat(0uL, length).ToArray()
                      : new ulong[length]);
    }

    public int Capacity => _bits.Length * 64;

    public bool Contains(int value)
        => (_bits[value >> 6] & 1uL << (value & 63)) != 0;

    public void Add(int value)
        => _bits[value >> 6] |= 1uL << (value & 63);

    public void Remove(int value)
        => _bits[value >> 6] &= ~(1uL << (value & 63));
}

internal static class UnitTest {
    private static void Main()
    {
        var bits = new BitSet(1000);

        for (var i = 0; i < 1000; i += 3) bits.Add(i);

        for (var i = 0; i != bits.Capacity; ++i)
            if (bits.Contains(i)) Console.Write($"{i} ");

        Console.WriteLine();
    }
}
