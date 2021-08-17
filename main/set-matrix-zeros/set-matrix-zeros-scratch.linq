<Query Kind="Program" />

public class Solution {
    public void SetZeroes(int[,] matrix) {
        // Get the dimensions and return if the matrix is 0x0.
        var m = matrix.GetLength(0);
        var n = matrix.GetLength(1);
        if (m == 0 || n == 0) return;
        
        // Record if the left column and top row will themselves be zeroed.
        var zeroTop = Enumerable.Range(0, n).Any(j => matrix[0, j] == 0);
        var zeroLeft = Enumerable.Range(0, m).Any(i => matrix[i, 0] == 0);
        
        // Use them to record which other rows and columns will be zeroed.
        for (var i = 1; i != m; ++i) {
            for (var j = 1; j != n; ++j)
                if (matrix[i, j] == 0) matrix[0, j] = matrix[i, 0] = 0;
        }
        
        // Zero out marked rows (but not the top row).
        for (var i = 1; i != m; ++i) {
            if (matrix[i, 0] == 0)
                for (var j = 1; j != n; ++j) matrix[i, j] = 0;
        }
        
        // Zero out marked columns (but not the left column).
        for (var j = 1; j != n; ++j) {
            if (matrix[0, j] == 0)
                for (var i = 1; i != m; ++i) matrix[i, j] = 0;
        }
        
        // Zero out the top row and/or left column, if appropriate.
        if (zeroTop)
            for (var j = 0; j != n; ++j) matrix[0, j] = 0;
        if (zeroLeft)
            for (var i = 0; i != m; ++i) matrix[i, 0] = 0;
    }
}

private static void Main() { }
