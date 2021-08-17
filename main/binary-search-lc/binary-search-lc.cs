public class Solution {
    private const int NotFound = -1;

    public int Search(int[] nums, int target) {
        var low = 0;
        var high = nums.Length - 1;
        
        while (low <= high) {
            var mid = low + (high - low) / 2;
            
            if (nums[mid] < target)
                low = mid + 1;
            else
                high = mid - 1;
        }
        
        return low == nums.Length || nums[low] != target ? NotFound : low;
    }
}
