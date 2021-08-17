#!/usr/bin/env python

from errno import ENOENT
from itertools import product
from os import remove
from sys import stdin

class Board(object):
    'A game board with unseen (o), clean (-), dirty (d), and bot (b) cells.'

    _NO_BOT = -1
    _CELL_STATES = ('o', '-', 'd', 'b')

    @staticmethod
    def _get_pair(infile):
        'Read a line from a file/device as a pair of ints.'
        return map(int, infile.readline().split())

    @staticmethod
    def _get(infile):
        'Read a line from a file/device as a stripped/trimmed character list.'
        return list(infile.readline().strip())

    def __init__(self, infile=None):
        'Make a blank board or deserialize a board from a file or device.'
        self._m = self._n = 5                            # board size

        if infile is None:
            self._bi = self._bj = Board._NO_BOT          # bot coordinates
            default_row = 'o' * self._n
            self._grid = [list(default_row) for dummy in xrange(self._m)]
        else:
            self._bi, self._bj = Board._get_pair(infile) # bot coordinates
            self._grid = [Board._get(infile) for dummy in xrange(self._m)]
            assert all(len(row) == self._n for row in self._grid)

    def _positions(self):
        'Generate all valid grid coordinates, in row-major order.'
        return product(xrange(self._m), xrange(self._n))

    def _same_size_as(self, other):
        'Check if self has the same number of rows and columns as other.'
        return self._m == other._m and self._n == other._n

    def _no_bot(self):
        'Check if the bot is absent (asserts unambiguous absence/presence).'
        if self._bi == Board._NO_BOT or self._bj == Board._NO_BOT:
            assert self._bi == self._bj
            return True

        return False

    def _erase_bot_avatar(self, draw_under='-'):
        'Undraw the bot. (Call this before a move.)'
        if self._grid[self._bi][self._bj] == 'b':
            self._grid[self._bi][self._bj] = draw_under

    def _draw_bot_avatar(self, draw_over=('-', 'o')):
        'Draw the bot. (Call this for a new board or after a move.)'
        if self._grid[self._bi][self._bj] in draw_over:
            self._grid[self._bi][self._bj] = 'b'

    def _copy_bot(self, other):
        'Copy the bot from other to self. (Helper function for _update_bot.)'
        assert not other._no_bot()

        self._bi = other._bi
        self._bj = other._bj

    def _update_bot(self, other):
        "Update self's bot coordinates from a second board (other)."
        if self._no_bot():
            self._copy_bot(other)
            self._draw_bot_avatar()
        else:
            assert self._bi == other._bi and self._bj == other._bj

    def _update_cell(self, other, i, j):
        'If (i, j) is unseen in self, update it from other.'
        assert self._grid[i][j] in Board._CELL_STATES
        assert other._grid[i][j] in Board._CELL_STATES

        if self._grid[i][j] == 'o':
            self._grid[i][j] = other._grid[i][j]

    def update(self, other):
        'Update the board with new information from a second board (other).'
        assert self._same_size_as(other)
        self._update_bot(other)

        for i, j in self._positions():
            self._update_cell(other, i, j)

    def _acquire_target(self, desired=('d', 'o')):
        'Find the cell coordinates that the bot is about to move to or clean.'
        min_distance = self._m + self._n
        found = False

        for state in desired:
            for i, j in self._positions():
                if self._grid[i][j] != state:
                    continue

                distance = abs(i - self._bi) + abs(j - self._bj)

                if distance < min_distance:
                    min_distance = distance
                    found = True

                    # set new target coordinates
                    ti = i
                    tj = j

            if found:
                return ti, tj

        raise ValueError('no targets found')

    def move(self):
        'Take a turn in the game. The bot either walks or cleans.'
        i, j = self._acquire_target()
        self._erase_bot_avatar()

        if self._bj < j:
            print 'RIGHT'
            self._bj += 1
        elif self._bj > j:
            print 'LEFT'
            self._bj -= 1
        elif self._bi < i:
            print 'DOWN'
            self._bi += 1
        elif self._bi > i:
            print 'UP'
            self._bi -= 1
        else:
            assert self._grid[i][j] == 'd'
            print 'CLEAN'
            self._grid[i][j] = '-'

        self._draw_bot_avatar()

    def _cell_is_clean(self, i, j):
        'Check if the cell at (i, j) is known to be clean.'
        return self._grid[i][j] in ('-', 'b')

    def is_clean(self):
        'Check if all cells in the grid are known to be clean.'
        return all(self._cell_is_clean(i, j) for i, j in self._positions())

    def _row(self, i):
        'Stringify the ith row.'
        return ''.join(self._grid[i])

    def save(self, outfile):
        'Serialize the board to a file, saving the game.'
        outfile.write('%d %d\n' % (self._bi, self._bj))
        outfile.writelines(self._row(i) + '\n' for i in xrange(self._m))

UUID = '4afa1ef8-d35d-447c-b907-d22526fdc827'
PATH = 'botcleanv2.%s.savegame' % UUID

try:
    with open(PATH, 'r') as f:
        board = Board(f)
except IOError as e:
    if e.errno == ENOENT:
        board = Board()
    else:
        raise

board.update(Board(stdin))

board.move()

if board.is_clean():
    remove(PATH)
else:
    with open(PATH, 'w') as f:
        board.save(f)
