<Query Kind="Program" />

public class Solution {
    public string LargestNumber(int[] nums)
        => string.Concat(nums.Select(val => val.ToString())
                             .OrderByDescending(digits => digits[0]));
}

internal static class UnitTest {
    private static void Main()
    {
        Test(10, 20);
        Test(3, 30, 34, 5, 9);
    }
    
    private static void Test(params int[] nums)
        => new Solution().LargestNumber(nums).Dump();
}
