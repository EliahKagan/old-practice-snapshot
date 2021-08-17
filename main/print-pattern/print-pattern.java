import java.util.Scanner;

final class Solution {
    private static final int STEP = 5;
    
    private static int stepwiseDown(final int start)
    {
        System.out.format("%d ", start);
        return start > 0 ? stepwiseDown(start - STEP) : start;
    }
    
    private static void stepwiseUp(final int start, final int stop)
    {
        if (start == stop) System.out.println(start);
        else {
            System.out.format("%d ", start);
            stepwiseUp(start + STEP, stop);
        }
    }
    
    private static void stepwiseDownUp(final int n)
    {
        stepwiseUp(stepwiseDown(n) + STEP, n);
    }
    
    private static void run(final Scanner sc, final int t)
    {
        if (t > 0) {
            stepwiseDownUp(sc.nextInt());
            run(sc, t - 1);
        }
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            run(sc, sc.nextInt());
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
