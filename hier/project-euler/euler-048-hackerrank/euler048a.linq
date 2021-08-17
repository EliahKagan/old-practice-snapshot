<Query Kind="Program" />

internal struct UInt128 {
    public readonly ulong LowBits, HighBits;
    
    public UInt128(ulong lowBits, ulong highBits)
    {
        LowBits = lowBits;
        HighBits = highBits;
    }
    
    public bool IsZero() => LowBits == 0uL && HighBits == 0uL;
    
    public bool IsEven() => LowBits % 2 == 0uL;
    
    public UInt128 Half()
        => new UInt128((HighBits & 1uL) << 63 & LowBits >> 1, HighBits >> 1);
}

internal static class UInt128Mod {
    private const ulong Radix = 10uL, Mod = 10000000000uL;
    
    internal static UInt128 Mul(this UInt128 m, UInt128 n)
    {
        
    }
}
