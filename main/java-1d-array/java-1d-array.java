import java.util.Scanner;

final class Utility {
    // Determines if every boolean value in an array is true.
    public static boolean isAllTrue(final boolean[] a)
    {
        for (final boolean b : a)
            if (!b) return false;
        
        return true;
    }
    
    private Utility() { } // the Utility class should not be instantiated
}

final class Game {
    // Reads a game into a boolean array (where false positions are blocked).
    public static boolean[] read(final int n, final Scanner sc)
    {
        final boolean[] a = new boolean[n];
        for (int i = 0; i != n; ++i) a[i] = sc.nextInt() == 0;
        return a;
    }
    
    // Determines if the game represented by the boolean array a (where false
    // positions are blocked) is winnable from the position i, returning true
    // if there is a winning game from there. NOTE: Destroys the contents of a.
    private static boolean playFrom(final boolean[] a, final int i,
                                    final boolean can_retreat, final int m)
    {
        if (!a[i]) return false;
        a[i] = false;
        
        final int j = i + m;
        if (j >= a.length) return true;
        
        return playFrom(a, j, true, m) || playFrom(a, i + 1, false, m)
                || (can_retreat && playFrom(a, i - 1,  true, m));
    }
    
    // Determines if the game represented by the boolean array a (where false
    // positions are blocked) is winnable, returning true if there is a winning
    // game and false otherwise. NOTE: Destroys the contents of a.
    public static boolean play(final boolean[] a, final int m)
    {
        return m < 2 ? Utility.isAllTrue(a) : playFrom(a, 0, false, m);
    }
    
    private Game() { } // the Game class should not be instantiated
}

final class Solution {
    // Runs the game for a single test case.
    private static void run(final Scanner sc)
    {
        final int n = sc.nextInt(), m = sc.nextInt();
        System.out.println(Game.play(Game.read(n, sc), m) ? "YES" : "NO");
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) run(sc);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
