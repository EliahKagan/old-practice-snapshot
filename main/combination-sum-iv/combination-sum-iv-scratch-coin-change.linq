<Query Kind="Program" />

public class Solution {
    public int CombinationSum4(int[] nums, int target) {
        // (index, subtot) => count
        var memo = new Dictionary<(int, int), int>();
        
        int Solve(int index, int subtot) {
            if (subtot == 0) return 1;
            if (index == nums.Length) return 0;
            
            var key = (index, subtot);
            if (!memo.TryGetValue(key, out var count)) {
                var value = nums[index++];
                for (; subtot >= 0; subtot -= value)
                    count += Solve(index, subtot);
                
                memo.Add(key, count);
            }
            
            return count;
        }
        
        var ret = Solve(0, target);
        memo.Dump();
        return ret;
        
        //return Solve(0, target);
    }
}

internal static class UnitTest {
    private static void Main() {
        var s = new Solution();
        s.CombinationSum4(new[] { 1, 2, 3 }, 4 ).Dump();
    }
}
