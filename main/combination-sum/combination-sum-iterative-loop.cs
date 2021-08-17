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
