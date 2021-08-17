import java.util.Scanner;

final class Solution {
    private static void run(int n, final Scanner sc)
    {
        final boolean [] a = new boolean[n + 1];
        
        for (boolean found = false; ; ) {
            final int i = sc.nextInt();
            
            if (!a[i]) a[i] = true;
            else if (found) {
                System.out.println(i);
                break;
            } else {
                System.out.format("%d ", i);
                found = true;
            }
        }
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = Integer.parseInt(sc.nextLine()); t > 0; --t) {
                final int n = Integer.parseInt(sc.nextLine());
                try (final Scanner scLine = new Scanner(sc.nextLine())) {
                    run(n, scLine);
                }
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
