BOARD_SIZE = 8

DIRECTIONS = ((-1, -1), (-1, 0), (-1, +1),
              (0, -1), (0, +1),
              (+1, -1), (+1, 0), (+1, +1))


def exists(i, j):
    """Tells if (i, j) is a valid 0-indexed position on an 8x8 board."""
    return 0 <= i < BOARD_SIZE and 0 <= j < BOARD_SIZE


def make_board(queens):
    """Makes a board of queens."""
    board = [[False] * BOARD_SIZE for _ in range(BOARD_SIZE)]

    for i, j in queens:
        if not exists(i, j):
            raise ValueError('queen position out of range')
        board[i][j] = True

    return board


def scan(board, i, j, di, dj):
    """Yields the first queen if any in the (di, dj) diretion from (i, j)."""
    while True:
        i += di
        j += dj

        if not exists(i, j):
            break

        if board[i][j]:
            yield i, j
            break


def attackers(board, ki, kj):
    """Yields all the queens in all eight directions from (ki, kj)."""
    if not exists(ki, kj):
        raise ValueError('king position out of range')

    for di, dj in DIRECTIONS:
        yield from scan(board, ki, kj, di, dj)


class Solution:
    def queensAttacktheKing(self, queens: List[List[int]], king: List[int]):
        """Returns a list of queens that can attack the given king."""
        return list(attackers(make_board(queens), *king))
