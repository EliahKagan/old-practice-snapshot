import java.util.*;

final class Solution {
    private static final StringBuilder buffer = new StringBuilder(6000000);
    private static final Deque<Runnable> undos = new ArrayDeque<>(); // stack
    
    private static int fromEnd(final int k)
    {
        return buffer.length() - k;
    }
    
    private static Runnable appender(final String w)
    {
        return () -> buffer.append(w);
    }
    
    private static Runnable eraser(final int k)
    {
        return () -> buffer.setLength(fromEnd(k));
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            sc.nextInt(); // ignore Q value; apparently it is unreliable
            
            while (sc.hasNext()) {
                switch (sc.nextInt()) {
                case 1: // append
                    final String w = sc.next();
                    appender(w).run();
                    undos.push(eraser(w.length()));
                    continue;
                    
                case 2: // erase
                    final int i = sc.nextInt();
                    undos.push(appender(buffer.substring(fromEnd(i))));
                    eraser(i).run();
                    continue;
                    
                case 3: // get
                    final int j = sc.nextInt() - 1;
                    System.out.println(buffer.charAt(j));
                    continue;
                    
                case 4: // undo
                    undos.pop().run();
                    continue;
                    
                default:
                    final String message = "invalid query type";
                    throw new UnsupportedOperationException(message);
                }
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
