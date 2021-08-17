<Query Kind="Program" />

public class Solution {
    public IList<IList<int>> CombinationSum2(int[] candidates, int target) {
        var len = candidates.Length;
        var combo = new bool[len];
        var ret = new List<IList<int>>();
        
        void Dfs(int index, int subtot) {
            if (subtot == 0) {
                ret.Add(Enumerable.Range(0, index)
                                  .Where(i => combo[i])
                                  .Select(i => candidates[i]).ToArray());
            }
            else if (index != len) {
                Dfs(index + 1, subtot);
                
                if ((subtot -= candidates[index]) >= 0) {
                    combo[index] = true;
                    Dfs(index + 1, subtot);
                    combo[index] = false;
                }
            }
        }
        
        Dfs(0, target);
        return ret;
    }
}

internal static class UnitTest {
    private static void Main() {
        var s = new Solution();
        s.CombinationSum2(new[] { 10, 1, 2, 7, 6, 1, 5 }, 8).Dump();
        //s.CombinationSum(new[] { 2, 3, 6, 7 }, 7).Dump();
        //s.CombinationSum(new[] { 1, 2, 3, 4, 5 }, 22).Dump();
    }
}
