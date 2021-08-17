<Query Kind="Program" />

public class Solution {
    private const int NotFound = -1;

    public int Search(int[] nums, int target) {
        var low = 0;
        var high = nums.Length - 1;
        
        while (low <= high) {
            var mid = low + (high - low) / 2;
            mid.Dump(nameof(mid));
            
            if (nums[mid] < target)
                low = mid + 1;
            else
                high = mid - 1;
        }
        
        low.Dump(nameof(low));
        high.Dump(nameof(high));
        
        return low == nums.Length || nums[low] != target ? NotFound : low;
    }
}

internal static class UnitTest {
    private static void Main()
    {
        var s = new Solution();
        var a = new[] {1, 1, 1, 1, 1, 1, 2, 3, 3, 3, 3, 3, 3, 3, 7, 7, 9, 14, 18, 33};
        s.Search(a, 7).Dump("result");
    }
}
