import java.util.*;

final class Solution {
    private static List<Integer> getRecord(int n, final Scanner sc)
    {
        final List<Integer> a = new ArrayList<>();
        while (n-- > 0) a.add(sc.nextInt());
        return a;
    }
    
    private static void editRecord(final List<Integer> a,
                                   int n, final Scanner sc)
    {
        while (n-- > 0) {
            switch (sc.next()) {
            case "Insert":
                final int i = sc.nextInt(), e = sc.nextInt();
                a.add(i, e);
                continue;
                
            case "Delete":
                a.remove(sc.nextInt());
                continue;
                
            default:
                throw new UnsupportedOperationException();
            }
        }
    }
    
    private static void putRecord(final List<Integer> a)
    {
        String sep = "";
        for (final int e : a) {
            System.out.format("%s%d", sep, e);
            sep = " ";
        }
        
        System.out.println();
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            final List<Integer> a = getRecord(sc.nextInt(), sc);
            editRecord(a, sc.nextInt(), sc);
            putRecord(a);
        }
    }
}
