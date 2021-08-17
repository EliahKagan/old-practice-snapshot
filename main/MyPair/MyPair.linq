<Query Kind="Program" />

// In real life, use Tuple<> or ValueTuple<> instead of this.
internal struct MyPair<T> : IEquatable<MyPair<T>> where T : IEquatable<T> {
    public static bool operator==(MyPair<T> lhs, MyPair<T> rhs)
        => lhs.Equals(rhs);
    
    public static bool operator!=(MyPair<T> lhs, MyPair<T> rhs)
        => !lhs.Equals(rhs);
    
    public readonly T First, Second;
    
    public MyPair(T first, T second)
    {
        First = first;
        Second = second;
    }

    public bool Equals(MyPair<T> rhs)
        => First.Equals(rhs.First) && Second.Equals(rhs.Second);
    
    public override bool Equals(object obj)
        => obj is MyPair<T> rhs && Equals(rhs);
    
    public override int GetHashCode()
        => First.GetHashCode() ^ unchecked(Second.GetHashCode() * hashingMultiplier);
    
    // See rationale by https://stackoverflow.com/users/21499/dr-hans-peter-störr
    // at https://stackoverflow.com/a/2816747. Note that this is a somewhat
    // different use case because the values being multiplied here are themselves
    // hash codes, possibly generated in a similar way, and because Störr's testing
    // was with a Java virtual machine. If this yields more hash collisions than
    // expected, blame me, not him!
    private const int hashingMultiplier = 92_821;
}

internal static class UnitTest {
    private static void Main()
    {
        const int r = 1000; // Manhattan metric
        
        var pairs = new HashSet<MyPair<int>>();
        var codes = new HashSet<int>();
        
        for (var i = -r; i <= r; ++i) {
            for (var j = -r; j <= r; ++j) {
                var ij = new MyPair<int>(i, j);
                pairs.Add(ij);
                codes.Add(ij.GetHashCode());
            }
        }
        
        var npairs = pairs.Count;
        var ncodes = codes.Count;
        var mean_pairs_per_code = (double)npairs / (double)ncodes;
        
        Console.WriteLine($"pairs.Count = {pairs.Count}");
        Console.WriteLine($"codes.Count = {codes.Count}");
        Console.WriteLine($"On average (NOT what matters most) ~{mean_pairs_per_code:F3} values share a code.");
    }
}
