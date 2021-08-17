public class Solution {
    public int MinimumTotal(IList<IList<int>> triangle) {
        if (triangle.Count == 0) return 0;

        var sums = new int[triangle.Count];
        triangle[triangle.Count - 1].CopyTo(sums, 0);

        for (var i = triangle.Count - 2; i >= 0; --i) {
            for (var j = 0; j <= i; ++j)
                sums[j] = Math.Min(sums[j], sums[j + 1]) + triangle[i][j];
        }

        return sums[0];
    }
}
