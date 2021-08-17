<Query Kind="Program" />

public class Solution {
    public IList<IList<int>> CombinationSum(int[] candidates, int target) {
        var len = candidates.Length;
        var ret = new List<IList<int>>();
        var path = new int[len];
        
        IEnumerable<int> CanonicalPath(int stop) {
            for (var pos = 0; pos != stop; ++pos) {
                var value = candidates[pos];
                for (var count = path[pos]; count != 0; --count)
                    yield return value;
            }
        }
        
        void Dfs(int index, int subtot) {
            if (subtot == 0) {
                ret.Add(CanonicalPath(index).ToArray());
                return;
            }
            
            if (index == len) return;
            
            for (var value = candidates[index]; subtot >= 0; subtot -= value) {
                Dfs(index + 1, subtot);
                ++path[index];
            }
            
            path[index] = 0;
        }
        
        Dfs(0, target);
        return ret;
    }
}

internal static class UnitTest {
    private static void Main() {
        var s = new Solution();
        s.CombinationSum(new[] { 2, 3, 6, 7 }, 7).Dump();
        s.CombinationSum(new[] { 1, 2, 3, 4, 5 }, 22).Dump();
    }
}
