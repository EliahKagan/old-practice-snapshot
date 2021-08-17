import java.util.*;

class Solution {
    public static void main(String[] args)
    {
        final Scanner sc = new Scanner(System.in);
        for (int t = sc.nextInt(); t > 0; --t) {
            try {
                final long n = sc.nextLong();
                System.out.format("%d can be fitted in:%n", n);

                if (Byte.MIN_VALUE <= n && n <= Byte.MAX_VALUE)
                    System.out.println("* byte");

                if (Short.MIN_VALUE <= n && n <= Short.MAX_VALUE)
                    System.out.println("* short");

                if (Integer.MIN_VALUE <= n && n <= Integer.MAX_VALUE)
                    System.out.println("* int");

                System.out.println("* long");
            }
            catch (InputMismatchException e) {
                System.out.format("%s can't be fitted anywhere.%n", sc.next());
            }
        }
    }
}
