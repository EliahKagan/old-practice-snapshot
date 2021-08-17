<Query Kind="Program" />

public readonly struct Pair<TFirst, TSecond>
    : IComparable<Pair<TFirst, TSecond>>, IEquatable<Pair<TFirst, TSecond>>
        where TFirst : IComparable<TFirst>, IEquatable<TFirst>
        where TSecond : IComparable<TSecond>, IEquatable<TSecond> {
    public static bool operator==(in Pair<TFirst, TSecond> lhs,
                                  in Pair<TFirst, TSecond> rhs)
        => lhs.Equals(in rhs);
    
    public static bool operator!=(in Pair<TFirst, TSecond> lhs,
                                  in Pair<TFirst, TSecond> rhs)
        => !lhs.Equals(in rhs);
    
    public static bool operator<(in Pair<TFirst, TSecond> lhs,
                                 in Pair<TFirst, TSecond> rhs)
        => lhs.CompareTo(in rhs) < 0;
    
    public static bool operator>(in Pair<TFirst, TSecond> lhs,
                                 in Pair<TFirst, TSecond> rhs)
        => lhs.CompareTo(in rhs) > 0;
    
    public static bool operator<=(in Pair<TFirst, TSecond> lhs,
                                  in Pair<TFirst, TSecond> rhs)
        => lhs.CompareTo(in rhs) <= 0;
    
    public static bool operator>=(in Pair<TFirst, TSecond> lhs,
                                  in Pair<TFirst, TSecond> rhs)
        => lhs.CompareTo(in rhs) >= 0;
    
    public Pair(TFirst first, TSecond second)
        => (First, Second) = (first, second);
    
    public void Deconstruct(out TFirst first, out TSecond second)
        => (first, second) = (First, Second);
    
    public int CompareTo(in Pair<TFirst, TSecond> other)
    {
        var byFirst = First.CompareTo(other.First);
        return byFirst != 0 ? byFirst : Second.CompareTo(other.Second);
    }
    
    int IComparable<Pair<TFirst, TSecond>>
            .CompareTo(Pair<TFirst, TSecond> other) => CompareTo(in other);
    
    public bool Equals(in Pair<TFirst, TSecond> other)
        => First.Equals(other.First) && Second.Equals(other.Second);
    
    bool IEquatable<Pair<TFirst, TSecond>>.Equals(Pair<TFirst, TSecond> other)
        => Equals(in other);
    
    public override bool Equals(object obj)
        => obj is Pair<TFirst, TSecond> other && Equals(in other);
    
    public override int GetHashCode()
    {
        const int p = 17;
        const int q = 31;
        
        var ret = p;
        ret = unchecked(ret * q + First.GetHashCode());
        ret = unchecked(ret * q + Second.GetHashCode());
        return ret;
    }
    
    public override string ToString() => $"({First}, {Second})";
    
    private object ToDump() => new { First, Second };
    
    public TFirst First { get; }
    public TSecond Second { get; }
}

public static class Pair {
    public static Pair<TFirst, TSecond>
    Create<TFirst, TSecond>(TFirst first, TSecond second)
            where TFirst : IComparable<TFirst>, IEquatable<TFirst>
            where TSecond : IComparable<TSecond>, IEquatable<TSecond>
        => new Pair<TFirst, TSecond>(first, second);
}

internal static class Program {
    private static void Swap<T>(ref T x, ref T y)
        => (x, y) = (y, x);
    
    private static void Main()
    {
        var s = "foo";
        var t = "bar";
        
        void Show() => new { s, t }.Dump();
        Show();
        
        Swap(ref s, ref t);
        Show();
        
        (s, t) = Tuple.Create("ham", "spam");
        Show();
        
        var (a, (b, c)) = Tuple.Create(10, Tuple.Create(20, 30));
        new { a, b, c }.Dump();
        
        var u = Pair.Create(1, Pair.Create(2, 3));
        u.Dump(nameof(u));
        
        var v = Pair.Create(1, Pair.Create(2, 3));
        (u == v).Dump($"{nameof(u)} == {nameof(v)}");
        
        var w = Pair.Create(1, Pair.Create(1, 4));
        (w < u).Dump($"{nameof(w)} < {nameof(u)}");
        
        var (x, (y, z)) = v;
        new { x, y, z }.Dump($"from {nameof(v)}");
        
        (x, (y, z)) = w;
        new { x, y, z }.Dump($"from {nameof(w)}");
    }
}
