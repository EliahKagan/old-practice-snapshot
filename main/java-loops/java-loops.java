class Solution {
    public static void main(String[] args)
    {
        java.util.Scanner sc = new java.util.Scanner(System.in);
        for (int t = sc.nextInt(); t > 0; --t) {
            int a = sc.nextInt(), b = sc.nextInt(), n = sc.nextInt();
            if (n < 1) continue;

            int sum = a + b; // a + 2^0 * b (i == 0)
            System.out.format("%d", sum);
            for (int i = 1; i != n; ++i)
                System.out.format(" %d", sum += b * (1 << i));

            System.out.println();
        }
    }
}
