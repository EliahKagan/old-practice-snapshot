class Solution {
    public List<List<String>> solveNQueens(int n) {
        if (n > 0) return new Backtracker(n).solve();
        if (n == 0) return Arrays.asList(Collections.emptyList());
        return Collections.emptyList();
    }
}

final class Backtracker {
    Backtracker(final int n) {
        _n = n;
        _board = new int[n];
        Arrays.fill(_board, NO_INDEX);

        final int diagonalCount = n * 2 - 1;
        _rises = new boolean[diagonalCount];
        _falls = new boolean[diagonalCount];

        makeLines();
    }

    List<List<String>> solve() {
        if (_used) throw new IllegalStateException("backtracker already used");
        _used = true;
        search(0);
        return _grids;
    }

    private void makeLines() {
        _lines = new String[_n];

        final StringBuilder buffer = new StringBuilder(_n);
        for (int i = 0; i != _n; ++i) buffer.append(EMPTY);

        for (int i = 0; i != _n; ++i) {
            buffer.setCharAt(i, QUEEN);
            _lines[i] = buffer.toString();
            buffer.setCharAt(i, EMPTY);
        }
    }

    private void search(final int i) {
        if (i == _n) {
            emit();
            return;
        }

        for (int j = 0; j != _n; ++j) {
            if (_board[j] != NO_INDEX) continue;

            final int riseIndex = i + j;
            if (_rises[riseIndex]) continue;

            final int fallIndex = _n - 1 + i - j;
            if (_falls[fallIndex]) continue;

            _board[j] = i;
            _rises[riseIndex] = _falls[fallIndex] = true;

            search(i + 1);

            _board[j] = NO_INDEX;
            _rises[riseIndex] = _falls[fallIndex] = false;
        }
    }

    private void emit()
    {
        final List<String> grid = new ArrayList<>(_n);
        for (int i = 0; i != _n; ++i) grid.add(_lines[_board[i]]);
        _grids.add(grid);
    }

    private static final int NO_INDEX = -1;

    private static final char EMPTY = '.';
    private static final char QUEEN = 'Q';

    private boolean _used = false;

    private final int _n;
    private final int[] _board;

    private final boolean[] _rises;
    private final boolean[] _falls;

    private final List<List<String>> _grids = new ArrayList<>();
    private String[] _lines;
}
