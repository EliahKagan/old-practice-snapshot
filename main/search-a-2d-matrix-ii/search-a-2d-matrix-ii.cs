public class Solution {
    public bool SearchMatrix(int[,] matrix, int target) {
        var m = matrix.GetLength(0);
        var n = matrix.GetLength(1);
        if (m == 0 || n == 0) return false;

        var i = 0;
        var j = n - 1;

        for (; ; ) {
            if (matrix[i, j] < target) {
                if (++i == m) return false;
            }
            else if (matrix[i, j] > target) {
                if (--j == -1) return false;
            }
            else return true;
        }
    }
}
