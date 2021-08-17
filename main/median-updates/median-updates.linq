<Query Kind="Program" />

internal struct TaggedInt : IComparable<TaggedInt>, IEquatable<TaggedInt> {
    public static TaggedInt MinOf(int value)
        => new TaggedInt(value, 0u);
    
    public static TaggedInt MaxOf(int value)
        => new TaggedInt(value, uint.MaxValue);

    public TaggedInt(int value) : this(value, checked(NextTag++)) { }
    
    public int CompareTo(TaggedInt other)
    {
        var byValue = Value.CompareTo(other.Value);
        return byValue != 0 ? byValue : Tag.CompareTo(other.Tag);
    }
    
    public bool Equals(TaggedInt other)
        => Value == other.Value && Tag == other.Tag;
    
    public override bool Equals(object rhs)
        => rhs is TaggedInt other && Equals(other);
    
    public override int GetHashCode() => Value;
    
    private TaggedInt(int value, uint tag)
    {
        Value = value;
        Tag = tag;
    }
    
    public bool IsDefault => Value == 0 && Tag == 0u;
    
    public readonly int Value;
    
    public readonly uint Tag;
    
    private static uint NextTag = 1u;
}

internal sealed class MedianPrinter {
    public void Add(int e)
    {
        var key = new TaggedInt(e);
        (_low.Count == 0 || e < _low.Max.Value ? _low : _high).Add(key);
        
        Rebalance();
        PrintMedian();
    }
    
    public void Remove(int e)
    {
        if ((RemoveFrom(_low, e) || RemoveFrom(_high, e))
                && (_low.Count != 0 || _high.Count != 0)) {
            Rebalance();
            PrintMedian();
        }
        else Console.WriteLine("Wrong!");
    }
    
    private static bool RemoveFrom(SortedSet<TaggedInt> set, int e)
    {
        var key = set.GetViewBetween(TaggedInt.MinOf(e), TaggedInt.MaxOf(e))
                     .FirstOrDefault();

        if (key.IsDefault) return false;
        
        set.Remove(key);
        return true;
    }
    
    private void Rebalance()
    {
        switch (SizeDelta) {
        case +2:
            var lowMax = _low.Max;
            _low.Remove(lowMax);
            _high.Add(lowMax);
            break;
            
        case -2:
            var highMin = _high.Min;
            _high.Remove(highMin);
            _low.Add(highMin);
            break;
            
        default:
            break; // _low and _high can't be made more balanced right now
        }
    }
    
    private void PrintMedian()
    {
        switch (SizeDelta) {
        case 0:
            // With an even number of values, take the mean of the middle two.
            var median = ((double)_low.Max.Value
                          + (double)_high.Min.Value) / 2.0;
            
            Console.WriteLine(median == Math.Floor(median) ? $"{median:F0}"
                                                           : $"{median:F1}");
            break;
            
        case +1:
            Console.WriteLine(_low.Max.Value);
            break;
            
        case -1:
            Console.WriteLine(_high.Min.Value);
            break;
            
        default:
            throw new InvalidOperationException(
                    "internal error: balancing invariant violated!");
        }
    }

    private int SizeDelta => _low.Count - _high.Count;

    private readonly SortedSet<TaggedInt> _low = new SortedSet<TaggedInt>();
    private readonly SortedSet<TaggedInt> _high = new SortedSet<TaggedInt>();
}

internal static class Solution {
    private static void Main()
    {
        var printer = new MedianPrinter();
    
        for (var n = int.Parse(Console.ReadLine()); n > 0; --n) {
            var tok = Console.ReadLine().Split();
            var op = tok[0];
            var arg = int.Parse(tok[1]);
            
            switch (op) {
            case "a":
                printer.Add(arg);
                break;
                
            case "r":
                printer.Remove(arg);
                break;
                
            default:
                throw new InvalidOperationException("unrecognized query type");
            }
        }
    }
}
