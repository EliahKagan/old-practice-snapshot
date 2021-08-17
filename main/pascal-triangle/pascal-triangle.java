import java.util.Scanner;

final class Solution {
    // Populates indices array with row indices read from standard input.
    // Returns the maximum index read.
    private static int readRowIndices(final int[] indices, final Scanner sc)
    {
        int max = 0;
        
        for (int k = 0; k != indices.length; ++k) {
            indices[k] = sc.nextInt() - 1;
            if (max < indices[k]) max = indices[k];
        }
        
        return max;
    }
    
    private static int[][] generatePascalsTriangle(final int height)
    {
        final int[][] triangle = new int[height][];
        triangle[0] = new int[] { 1 };
        
        for (int i = 1; i < height; ++i) {
            triangle[i] = new int[i + 1];
            triangle[i][i] = triangle[i][0] = 1;
            for (int j = 1; j < i; ++j)
                triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
        
        return triangle;
    }
    
    private static void printRow(final int[] row)
    {
        final int jmax = row.length - 1;
        for (int j = 0; j < jmax; ++j) System.out.format("%d ", row[j]);
        System.out.println(row[jmax]);
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            final int[] indices = new int[sc.nextInt()];
            final int height = readRowIndices(indices, sc) + 1;
            final int[][] triangle = generatePascalsTriangle(height);
            
            for (final int i : indices) printRow(triangle[i]);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
