public class Solution {
    public int CanCompleteCircuit(int[] gas, int[] cost) {
        var len = gas.Length;
        if (cost.Length != len)
            throw new ArgumentException("lengths don't match");

        // Make the gas array store deltas, and compute the total sum
        // and minimum partial sum when one starts at the initial index.
        var sum = 0;
        var min = 0;
        for (var i = 0; i != len; ++i) {
            sum += gas[i] -= cost[i];
            if (min > sum) min = sum;
        }

        if (sum < 0) return -1;

        for (var i = 0; ; ++i) {
            if (min >= 0) return i;
            min -= gas[i];
        }
    }
}
