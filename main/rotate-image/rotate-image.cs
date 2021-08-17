public class Solution {
    public void Rotate(int[,] matrix) {
        if (matrix.GetLength(0) != matrix.GetLength(1))
            throw new ArgumentException("matrix not square", nameof(matrix));

        // A 90-degree clockwise rotation is the same as a transposition
        // followed by a reflection about the vertical axis.
        Transpose(matrix);
        VerticalReflect(matrix);
    }

    private static void Transpose(int[,] matrix) {
        var n = matrix.GetLength(0);
        for (var i = 0; i < n - 1; ++i) {
            for (var j = i + 1; j < n; ++j) {
                var tmp = matrix[i, j];
                matrix[i, j] = matrix[j, i];
                matrix[j, i] = tmp;
            }
        }
    }

    private static void VerticalReflect(int[,] matrix) {
        var n = matrix.GetLength(0);
        for (var i = 0; i < n; ++i) {
            for (var j = 0; j < n / 2; ++j) {
                var tmp = matrix[i, j];
                matrix[i, j] = matrix[i, n - 1 - j];
                matrix[i, n - 1 - j] = tmp;
            }
        }
    }
}
