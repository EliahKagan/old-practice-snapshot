final class Solution {
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                int sum = 0;
                
                final String n = sc.next();
                for (int i = 0; i != n.length(); ++i) {
                    switch (n.charAt(i)) {
                        case '2':   sum += 2;   break;
                        case '3':   sum += 3;   break;
                        case '5':   sum += 5;   break;
                        case '7':   sum += 7;   break;
                    }
                }
                
                System.out.println(sum);
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}