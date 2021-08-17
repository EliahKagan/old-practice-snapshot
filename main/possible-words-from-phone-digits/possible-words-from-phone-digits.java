final class Solution {
    private static String[] multiply(final String[] a, final String[] b)
    {
        final String[] c = new String[a.length * b.length];
        
        int k = 0;
        for (int i = 0; i != a.length; ++i)
            for (int j = 0; j != b.length; ++j) c[k++] = a[i] + b[j];
        
        return c;
    }
    
    private static void print(final String[] a)
    {
        final int n = a.length - 1;
        for (int i = 0; i != n; ++i) System.out.format("%s ", a[i]);
        System.out.println(a[n]);
    }
    
    public static void main(final String[] args)
    {
        final String[][] keypad = { null, null, { "a", "b", "c" }, //0-2
            { "d", "e", "f" }, { "g", "h", "i" }, { "j", "k", "l" }, //3-5
            { "m", "n", "o" }, { "p", "q", "r", "s" }, { "t", "u", "v" }, //6-8
            { "w", "x", "y", "z" } }; //9
        
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                int n = sc.nextInt();
                String[] acc = keypad[sc.nextInt()];
                while (--n > 0) acc = multiply(acc, keypad[sc.nextInt()]);
                
                print(acc);
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
