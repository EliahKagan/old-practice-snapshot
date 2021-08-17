import java.util.Scanner;

final class Board {
    private static final int NO_PATH = -1;

    Board(final Scanner sc) {
        final int height = sc.nextInt(), width = sc.nextInt();
        _vis = new boolean[height][width];

        for (int i = 0; i != height; ++i) {
            final String row = sc.next();

            for (int j = 0; j != width; ++j) {
                switch (row.charAt(j)) {
                case 'M':
                    _iStart = i;
                    _jStart = j;
                    break;

                case '*':
                    _iEnd = i;
                    _jEnd = j;
                    break;

                case 'X':
                    _vis[i][j] = true;
                    break;
                }
            }
        }
    }

    int countJunctions() {
        return dfs(_iStart, _jStart);
    }

    private int dfs(final int i, final int j) {
        if (!canGo(i, j)) return NO_PATH;
        if (i == _iEnd && j == _jEnd) return 0;
        final int outdeg = countNeighbors(i, j);
        if (outdeg == 0) return NO_PATH;

        final int delta = (outdeg == 1 ? 0 : 1);
        _vis[i][j] = true;

        final int west = dfs(i, j - 1);
        if (west != NO_PATH) return delta + west;

        final int east = dfs(i, j + 1);
        if (east != NO_PATH) return delta + east;

        final int north = dfs(i - 1, j);
        if (north != NO_PATH) return delta + north;

        final int south = dfs(i + 1, j);
        if (south != NO_PATH) return delta + south;

        _vis[i][j] = false;
        return NO_PATH;
    }

    private int countNeighbors(final int i, final int j) {
        int outdeg = 0;

        if (canGo(i, j - 1)) ++outdeg;
        if (canGo(i, j + 1)) ++outdeg;
        if (canGo(i - 1, j)) ++outdeg;
        if (canGo(i + 1, j)) ++outdeg;

        return outdeg;
    }

    private boolean canGo(final int i, final int j) {
        return exists(i, j) && !_vis[i][j];
    }

    private boolean exists(final int i, final int j) {
        return 0 <= i && i < _vis.length && 0 <= j && j < _vis[i].length;
    }

    private final boolean[][] _vis;

    private int _iStart = -1, _jStart = -1, _iEnd = -1, _jEnd = -1;
}

final class Solution {
    public static void main(final String[] args) {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int answer = new Board(sc).countJunctions();
                final int guess = sc.nextInt();
                System.out.println(guess == answer ? "Impressed" : "Oops!");
            }
        }
    }

    private Solution() {
        throw new AssertionError();
    }
}
