<Query Kind="Program" />

public class Solution {
    public IList<IList<int>> Subsets(int[] nums) {
        var powerset = new IList<int>[1 << nums.Length];
        powerset[0] = new int[0];
        
        var len = 1;
        foreach (var element in nums) {
            var j = len;
            for (var i = 0; i != len; ++i, ++j) {
                var oldSubset = powerset[i];
                var oldLength = oldSubset.Count;
                var newSubset = new int[oldLength + 1];
                oldSubset.CopyTo(newSubset, 0);
                newSubset[oldLength] = element;
                powerset[j] = newSubset;
            }
            len = j;
        }
        
        Debug.Assert(len == powerset.Length);
        return powerset;
    }
}

private static void Main() {
    new Solution().Subsets(new[] { 1, 2, 3 }).Dump();
}
