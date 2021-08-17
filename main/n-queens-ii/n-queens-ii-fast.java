class Solution {
    public int totalNQueens(final int n) {
        if (n > 0) return new Backtracker(n).solve();
        if (n == 0) return 1;
        return 0;
    }
}

final class Backtracker {
    Backtracker(final int n) {
        _n = n;
        _cols = new boolean[n];

        final int diagonalCount = n * 2 - 1;
        _rises = new boolean[diagonalCount];
        _falls = new boolean[diagonalCount];
    }

    int solve() {
        return search(0);
    }

    private int search(final int i) {
        if (i == _n) return 1;

        int acc = 0;

        for (int j = 0; j != _n; ++j) {
            if (_cols[j]) continue;

            final int riseIndex = i + j;
            if (_rises[riseIndex]) continue;

            final int fallIndex = _n - 1 + i - j;
            if (_falls[fallIndex]) continue;

            _cols[j] = _rises[riseIndex] = _falls[fallIndex] = true;
            acc += search(i + 1);
            _cols[j] = _rises[riseIndex] = _falls[fallIndex] = false;

        }

        return acc;
    }

    private final int _n;
    private final boolean[] _cols, _rises, _falls;
}
