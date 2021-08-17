final class Solution {
    public static void main(String[] args)
    {
        final java.util.Scanner sc = new java.util.Scanner(System.in);
        final String s = sc.nextLine();
        final int k = sc.nextInt(), n = s.length() - k + 1;

        String ss_min = s.substring(0, k), ss_max = ss_min;
        for (int i = 1; i < n; ++i) {
            final String ss = s.substring(i, i + k);

            if (ss.compareTo(ss_min) < 0)
                ss_min = ss;
            else if (ss.compareTo(ss_max) > 0)
                ss_max = ss;
        }

        System.out.println(ss_min);
        System.out.println(ss_max);
    }

    private Solution() { } // this class should not be instantiated
}
