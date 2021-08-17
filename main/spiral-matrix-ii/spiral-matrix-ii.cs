public class Solution {
    public int[,] GenerateMatrix(int n) {
        var matrix = new int[n, n];

        var left = 0;
        var right = n - 1;
        var top = 0;
        var bottom = n - 1;

        var i = top;
        var j = left - 1;

        for (var elem = 1; ; ) {
            if (j == right) break;
            do matrix[i, ++j] = elem++;
            while (j < right);
            ++top;

            if (i == bottom) break;
            do matrix[++i, j] = elem++;
            while (i < bottom);
            --right;

            if (j == left) break;
            do matrix[i, --j] = elem++;
            while (j > left);
            --bottom;

            if (i == top) break;
            do matrix[--i, j] = elem++;
            while (i > top);
            ++left;
        }

        return matrix;
    }
}
