<Query Kind="Program" />

internal sealed class DisjointSetElement {
    internal DisjointSetElement() => Parent = this;
    
    internal DisjointSetElement FindSet() {
        var ret = this;
        while (ret.Parent != ret) ret = ret.Parent;
        
        for (var cur = this; cur != ret; ) { // path compression
            var next = cur.Parent;
            cur.Parent = ret;
            cur = next;
        }
        
        return ret;
    }
    
    internal void Union(DisjointSetElement other) {
        var a = FindSet();
        var b = other.FindSet();
        
        if (a.Rank < b.Rank) {
            a.Parent = b;
        } else {
            if (a.Rank == b.Rank) ++a.Rank;
            b.Parent = a;
        }
    }
    
    internal DisjointSetElement Parent { get; private set; }
    
    private int Rank { get; set; } = 0;
}

internal sealed class DisjointSets<T> : ICollection<T[]> {
    public void Add(IEnumerable<T> subset) {
        using (var en = subset.GetEnumerator()) {
            if (!en.MoveNext()) return;
            
            for (var first = GetElement(en.Current); en.MoveNext(); )
                GetElement(en.Current).Union(first);
        }
    }    
    
    public IEnumerator<T[]> GetEnumerator() {
        foreach (var group in _elems.GroupBy(kv => kv.Value.FindSet())) {
            var a = group.Select(kv => kv.Key).ToArray();
            Array.Sort(a);
            yield return a;
        }
    }
    
    public void Clear() => _elems.Clear();
    
    public int Count => _elems.Count;
    
    public bool IsReadOnly => false;
    
    IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();
    
    void ICollection<T[]>.Add(T[] subset) => Add(subset);
    
    bool ICollection<T[]>.Contains(T[] subset)
        => throw new NotSupportedException("can't query for exact subset");
    
    void ICollection<T[]>.CopyTo(T[][] array, int index)
        => throw new NotSupportedException("copying to array is unsuppported");
    
    bool ICollection<T[]>.Remove(T[] subset)
        => throw new NotSupportedException("can't remove subset");
    
    private DisjointSetElement GetElement(T key) {
        if (!_elems.TryGetValue(key, out var elem)) {
            elem = new DisjointSetElement();
            _elems.Add(key, elem);
        }
        
        return elem;
    }
    
    private readonly Dictionary<T, DisjointSetElement> _elems =
            new Dictionary<T, DisjointSetElement>();
}

internal static class Account {
    internal static string Name(this IEnumerable<string> account)
        => account.First();
    
    internal static IEnumerable<string>
    Emails(this IEnumerable<string> account)
        => account.Skip(1);
}

public class Solution {
    public IList<IList<string>> AccountsMerge(IList<IList<string>> accounts) {
        throw new NotImplementedException();
    }
}

private static void Main() {
    var accounts = new IList<string>[] {
        new[] {"John", "johnsmith@mail.com", "john00@mail.com"},
        new[] {"John", "johnnybravo@mail.com"},
        new[] {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
        new[] {"Mary", "mary@mail.com"}
    };
    
    //foreach (var g in accounts.GroupBy(Account.Name)) g.Dump("item");
    
    accounts.GroupBy(Account.Name).Select(g => g.Key).Dump();
    
}