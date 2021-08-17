public class Solution {
    public IList<IList<int>> Subsets(int[] nums) {
        IEnumerable<List<int>> SubsetsTo(int stop) {
            if (stop == 0) {
                yield return new List<int>();
                yield break;
            }

            var element = nums[stop - 1];

            foreach (var withoutElement in SubsetsTo(stop - 1)) {
                yield return withoutElement;

                var withElement = new List<int>(withoutElement.Count + 1);
                withElement.AddRange(withoutElement);
                withElement.Add(element);
                yield return withElement;
            }
        }

        return SubsetsTo(nums.Length).Select(subset => (IList<int>)subset)
                                     .ToList();
    }
}
