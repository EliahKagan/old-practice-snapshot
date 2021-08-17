import java.util.Scanner;
import java.util.function.IntBinaryOperator;
import java.util.stream.IntStream;

final class Solution {
    private static final int UNKNOWN = -1;
    
    private static int[] readRow(final Scanner sc, final int i)
    {
        return IntStream.range(0, i).map(j -> sc.nextInt()).toArray();
    }
    
    private static int[][] readGrid(final Scanner sc)
    {
        return IntStream.rangeClosed(1, sc.nextInt())
                        .mapToObj(i -> readRow(sc, i))
                        .toArray(int[][]::new);
    }
    
    private static int[] makeBlankRow(final int i)
    {
        return IntStream.range(0, i).map(j -> -1).toArray();
    }
    
    private static int[][] makeBlankGrid(final int n)
    {
        return IntStream.rangeClosed(1, n)
                        .mapToObj(Solution::makeBlankRow)
                        .toArray(int[][]::new);
    }
    
    private static int computeMaxPathSum(final int[][] grid)
    {
        final int[][] memo = makeBlankGrid(grid.length);
        
        final IntBinaryOperator dfs = new IntBinaryOperator() {
            @Override
            public int applyAsInt(final int i, final int j)
            {
                if (i == grid.length) return 0;
                
                if (memo[i][j] == UNKNOWN) {
                    final int left = applyAsInt(i + 1, j);
                    final int right = applyAsInt(i + 1, j + 1);
                    memo[i][j] = grid[i][j] + Math.max(left, right);
                }
                
                return memo[i][j];
            }
        };
        
        return dfs.applyAsInt(0, 0);
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(computeMaxPathSum(readGrid(sc)));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
