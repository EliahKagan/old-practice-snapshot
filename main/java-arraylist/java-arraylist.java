import java.util.*;

final class Solution {
    private static List<Integer> getRecord(final Scanner sc)
    {
        int d = sc.nextInt();
        List<Integer> rec = new ArrayList<>(d);
        while (d-- > 0) rec.add(sc.nextInt());
        return rec;
    }
    
    private static List<List<Integer>> getAllRecords(final Scanner sc)
    {
        int n = sc.nextInt();
        List<List<Integer>> records = new ArrayList<>(n);
        while (n-- > 0) records.add(getRecord(sc));
        return records;
    }
    
    private static String query(final List<List<Integer>> records,
                                int x, int y)
    {
        final List<Integer> rec = records.get(--x);
        return 0 < y && y <= rec.size() ? rec.get(--y).toString() : "ERROR!";
    }
    
    private static void runQueries(final List<List<Integer>> records,
                                   final Scanner sc)
    {
        for (int q = sc.nextInt(); q > 0; --q) {
            int x = sc.nextInt(), y = sc.nextInt();
            System.out.println(query(records, x, y));
        }
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            runQueries(getAllRecords(sc), sc);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
