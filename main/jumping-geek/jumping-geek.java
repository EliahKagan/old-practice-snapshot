final class Solution {
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                switch (sc.nextInt() % 6) {
                case 0: case 1: case 3:
                    System.out.println("yes");
                    break;
                    
                default:
                    System.out.println("no");
                }
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
