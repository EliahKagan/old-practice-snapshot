class Solution {
    public static void main(String[] args)
    {
        String hr = "================================";
        System.out.println(hr);

        java.util.Scanner sc = new java.util.Scanner(System.in);
        for (int i = 0; i < 3; ++i) {
            String s = sc.next();
            int n = sc.nextInt();
            System.out.format("%-15s%03d%n", s, n);
        }

        System.out.println(hr);
    }
}
