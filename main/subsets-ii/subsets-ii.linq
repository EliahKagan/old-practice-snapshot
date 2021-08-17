<Query Kind="Program" />

public class Solution {
    private struct Entry {
        internal Entry(int value, int count) {
            Value = value;
            Count = count;
        }
    
        internal readonly int Value, Count;
    }
    
    private IList<IList<int>> SubsetsWithDup(List<Entry> entries) {
        var powerset = new List<IList<int>> { new List<int>() };
        
        foreach (var ent in entries) {
            var deltaRange = Enumerable.Range(1, ent.Count);
            var value = ent.Value;
        
            foreach (var i in Enumerable.Range(0, powerset.Count)) {
                var oldSubset = powerset[i];
                var oldCount = oldSubset.Count;
                
                foreach (var delta in deltaRange) {
                    var newSubset = new List<int>(oldCount + delta);
                    newSubset.AddRange(oldSubset);
                    newSubset.AddRange(Enumerable.Repeat(value, delta));
                    powerset.Add(newSubset);
                }
            }
        }
        
        return powerset;
    }
    
    public IList<IList<int>> SubsetsWithDup(int[] nums)
        => SubsetsWithDup(nums.GroupBy(x => x)
                              .Select(g => new Entry(g.Key, g.Count()))
                              .OrderBy(ent => ent.Value) // not strictly needed
                              .ToList());
}

private static void Main() {
    var s = new Solution();
    s.SubsetsWithDup(new[] { 1, 2, 2, 3 }).Dump();
}
