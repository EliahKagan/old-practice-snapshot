public class Solution {
    public IList<int> SpiralOrder(int[,] matrix) {
        var ret = new List<int>();

        var left = 0;
        var right = matrix.GetLength(1) - 1;
        var top = 0;
        var bottom = matrix.GetLength(0) - 1;

        var i = top;
        var j = left - 1;

        for (; ; ) {
            if (j == right) break;
            do ret.Add(matrix[i, ++j]);
            while (j < right);
            ++top;

            if (i == bottom) break;
            do ret.Add(matrix[++i, j]);
            while (i < bottom);
            --right;

            if (j == left) break;
            do ret.Add(matrix[i, --j]);
            while (j > left);
            --bottom;

            if (i == top) break;
            do ret.Add(matrix[--i, j]);
            while (i > top);
            ++left;
        }

        return ret;
    }
}
