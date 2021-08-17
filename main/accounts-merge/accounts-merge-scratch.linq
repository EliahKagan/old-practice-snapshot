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

internal sealed class DisjointSets : IEnumerable<IOrderedEnumerable<string>>,
                                     ICollection<IEnumerable<string>> {
    public void Add(IEnumerable<string> subset) {
        using (var en = subset.GetEnumerator()) {
            if (!en.MoveNext()) return;
            
            for (var first = GetElement(en.Current); en.MoveNext(); )
                GetElement(en.Current).Union(first);
        }
    }
    
    public IEnumerator<IOrderedEnumerable<string>> GetEnumerator()
        => _elems.GroupBy(kv => kv.Value.FindSet())
                 .Select(grp => grp.Select(kv => kv.Key)
                                   .OrderBy(x => x, StringComparer.Ordinal))
                 .GetEnumerator();
    
    public void Clear() => _elems.Clear();
    
    public int Count => _elems.Count;
    
    public bool IsReadOnly => false;
    
    IEnumerator<IEnumerable<string>>
    IEnumerable<IEnumerable<string>>.GetEnumerator()
        => GetEnumerator();
    
    IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();
    
    void ICollection<IEnumerable<string>>.Add(IEnumerable<string> subset)
        => Add(subset);
    
    bool ICollection<IEnumerable<string>>.Contains(IEnumerable<string> subset)
        => throw new NotSupportedException(
                "exact subset query is unsupported");
    
    void ICollection<IEnumerable<string>>.CopyTo(IEnumerable<string>[] array,
                                                 int index)
        => throw new NotSupportedException("copying to array is unsuppported");
    
    bool ICollection<IEnumerable<string>>.Remove(IEnumerable<string> subset)
        => throw new NotSupportedException(
                "subset removal is unsupported");
    
    private DisjointSetElement GetElement(string key) {
        if (!_elems.TryGetValue(key, out var elem)) {
            elem = new DisjointSetElement();
            _elems.Add(key, elem);
        }
        
        return elem;
    }
    
    private readonly Dictionary<string, DisjointSetElement> _elems =
            new Dictionary<string, DisjointSetElement>();
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
        var ret = new List<IList<string>>();
        var sets = new DisjointSets();
        
        foreach (var grp in accounts.GroupBy(Account.Name)) {
            var name = new[] { grp.Key };
            foreach (var account in grp) sets.Add(account.Emails());
            foreach (var set in sets) ret.Add(name.Concat(set).ToArray());
            sets.Clear();
        }
        
        return ret;
    }
}

internal static class UnitTest {
    private static void PreTest() {
        var sets = new DisjointSets() {
            new[] { "johnsmith@mail.com", "john00@mail.com" },
            new[] { "johnnybravo@mail.com" },
            new[] { "johnsmith@mail.com", "john_newyork@mail.com" }
        };
        
        sets.Dump("pre-test");
    }

    private static void Main() {
        PreTest();
    
        var accounts = new IList<string>[] {
            new[] {"John", "johnsmith@mail.com", "john00@mail.com"},
            new[] {"John", "johnnybravo@mail.com"},
            new[] {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
            new[] {"Mary", "mary@mail.com"}
        };
        
        new Solution().AccountsMerge(accounts).Dump("main test");
    }
}