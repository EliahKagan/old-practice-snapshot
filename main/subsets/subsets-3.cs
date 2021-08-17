public class Solution {
    public IList<IList<int>> Subsets(int[] nums) {
        IEnumerable<int> MakeSubset(int mask) {
            foreach (var element in nums) {
                if ((mask & 1) != 0) yield return element;
                mask >>= 1;
            }
        }

        var powerset = new IList<int>[1 << nums.Length];

        for (var i = 0; i != powerset.Length; ++i)
            powerset[i] = MakeSubset(i).ToList();

        return powerset;
    }
}
