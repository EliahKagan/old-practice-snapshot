public class Solution {
    public int MinimumTotal(IList<IList<int>> triangle) {
        if (triangle.Count == 0) return 0;

        for (var i = triangle.Count - 2; i >= 0; --i) {
            for (var j = triangle[i].Count - 1; j >= 0; --j) {
                triangle[i][j] += Math.Min(triangle[i + 1][j],
                                           triangle[i + 1][j + 1]);
            }
        }

        return triangle[0][0];
    }
}
