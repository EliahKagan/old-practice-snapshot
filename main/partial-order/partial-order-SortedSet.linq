<Query Kind="Program" />

internal struct TaggedInt : IComparable<TaggedInt>, IEquatable<TaggedInt> {
    public readonly int Value, Tag;
    
    public TaggedInt(int value) {
        Value = value;
        Tag = ++LastId;
    }
    
    public int CompareTo(TaggedInt other)
        => Value.CompareTo(other.Value);
    
    public bool Equals(TaggedInt other)
        => Value == other.Value && Tag == other.Tag;
    
    public override bool Equals(object other)
        => other is TaggedInt rhs && Equals(rhs);
    
    public override int GetHashCode() => Value;
    
    private static int LastId = 0;
}

private static void Main() {
    var i = new TaggedInt(5);
    var j = new TaggedInt(3);
    var k = new TaggedInt(5);
    
    i.Dump();
    j.Dump();
    k.Dump();
    
    i.CompareTo(j).Dump();
    i.CompareTo(k).Dump();
    j.CompareTo(k).Dump();
    
    var s = new SortedSet<TaggedInt> { i, j, k };
    s.Dump();
}
