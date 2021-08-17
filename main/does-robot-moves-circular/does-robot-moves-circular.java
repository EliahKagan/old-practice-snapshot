final class Solution {
    private static final int NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3;
    private static final int BEARING_COUNT = 4, BEAR_LEFT = 3, BEAR_RIGHT = 1;
    
    private static boolean isCircular(final String moves)
    {
        int x = 0, y = 0, bearing = NORTH;
        
        for (int i = 0; i != moves.length(); ++i) {
            switch (moves.charAt(i)) {
            case 'G':
                switch (bearing) {
                    case NORTH:     ++y;    continue;
                    case EAST:      ++x;    continue;
                    case SOUTH:     --y;    continue;
                    case WEST:      --x;    continue;
                    default: throw new IllegalStateException();
                }
                
            case 'L':
                bearing = (bearing + BEAR_LEFT) % BEARING_COUNT;
                continue;
                
            case 'R':
                bearing = (bearing + BEAR_RIGHT) % BEARING_COUNT;
                continue;
                
            default:
                throw new UnsupportedOperationException();
            }
        }
        
        return x == 0 && y == 0;
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                System.out.println(isCircular(sc.next()) ? "Circular"
                                                         : "Not Circular");
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
