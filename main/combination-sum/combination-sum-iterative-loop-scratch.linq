<Query Kind="Program" />

public class Solution {
    public IList<IList<int>> CombinationSum(int[] candidates, int target) {
        var len = candidates.Length;
        var ret = new List<IList<int>>();
        var counts = new int[len];
        
        IEnumerable<int> CanonicalPath(int j) {
            for (var i = 0; i != j; ++i) {
                var value = candidates[i];
                for (var c = counts[i]; c != 0; --c) yield return value;
            }
        }
        
        for (var j = -1; ; ) {
            // advance
            if (target == 0) ret.Add(CanonicalPath(++j).ToArray());
            else j = len;
            
            // retreat
            for (; ; ) {
                if (j-- == 0) return ret;
                
                ++counts[j];
                target -= candidates[j];
                if (target >= 0) break;
                
                target += candidates[j] * counts[j];
                counts[j] = 0;
            }
        }
    }
}

internal static class UnitTest {
    private static void Main() {
        var s = new Solution();
        s.CombinationSum(new[] { 2, 3, 6, 7 }, 7).Dump();
        s.CombinationSum(new[] { 1, 2, 3, 4, 5 }, 22).Dump();
    }
}