<Query Kind="Program" />

// In real life, use Tuple<> or ValueTuple<> instead of this class.
internal sealed class MyRefPair<T> : IEquatable<MyRefPair<T>>
        where T : IEquatable<T> {
    public static bool operator==(MyRefPair<T> lhs, MyRefPair<T> rhs)
    {
        if (object.ReferenceEquals(lhs, rhs)) return true;
        if (object.ReferenceEquals(null, rhs)) return false;
        return lhs.First.Equals(rhs.First) && lhs.Second.Equals(rhs.Second);
    }
    
    public static bool operator!=(MyRefPair<T> lhs, MyRefPair<T> rhs)
        => !(lhs == rhs);
    
    public T First { get; private set; }
    public T Second { get; private set; }
    
    public MyRefPair()
        => First = Second = default(T);
    
    public MyRefPair(T first, T second)
    {
        First = first;
        Second = second;
    }
    
    public bool Equals(MyRefPair<T> rhs)
        => this == rhs;
    
    public override bool Equals(object obj)
        => Equals(obj as MyRefPair<T>);
    
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
        
        var pairs = new HashSet<MyRefPair<int>>();
        var codes = new HashSet<int>();
        
        for (var i = -r; i <= r; ++i) {
            for (var j = -r; j <= r; ++j) {
                var ij = new MyRefPair<int>(i, j);
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
