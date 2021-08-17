public class Solution {
    private const int Unknown = -1;

    private static int[] GetInitialMemoTable(int target) {
        var memo = new int[target + 1];
        memo[0] = 1;
        for (var i = 1; i <= target; ++i) memo[i] = Unknown;
        return memo;
    }

    public int CombinationSum4(int[] nums, int target) {
        var memo = GetInitialMemoTable(target); // subtot => count

        int Solve(int subtot) {
            var count = memo[subtot];

            if (count == Unknown) {
                memo[subtot] = count = nums.Select(value => subtot - value)
                                           .Where(delta => delta >= 0)
                                           .Sum(Solve);
            }

            return count;
        }

        return Solve(target);
    }
}
