import java.util.Scanner;

final class Solution {
    private static int[][] readMatrix(final Scanner sc)
    {
        final int m = sc.nextInt(), n = sc.nextInt();
        final int[][] matrix = new int[m][n];
        
        for (final int[] row : matrix)
            for (int j = 0; j != n; ++j) row[j] = sc.nextInt();
        
        return matrix;
    }
    
    private static boolean searchMatrix(final int[][] matrix, final int key)
    {
        final int m = matrix.length, n = matrix[0].length;
        
        for (int i = m - 1, j = 0; ; ) {
            final int value = matrix[i][j];
            
            if (value == key) return true;
            
            if (value < key) {
                ++j;
                if (j == n) return false;
            } else {
                --i;
                if (i == -1) return false;
            }
        }
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int[][] matrix = readMatrix(sc);
                System.out.println(searchMatrix(matrix, sc.nextInt()) ? 1 : 0);
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
