#!/usr/bin/env python3

import sys
from itertools import chain

FUSE_TIME = 3
NORMAL_RULES_START = 2
PLANTING_PERIOD = 2

EMPTY_SYMBOL = '.'
BOMB_SYMBOL = 'O'

if any(arg == '-v' or arg == '--verbose' for arg in sys.argv[1:]):
    def log(*values):
        print(sys.argv[0] + ':', *values, file=sys.stderr)
else:
    def log(*values):
        pass

def read_row():
    return [(FUSE_TIME if ch == BOMB_SYMBOL else 0) for ch in input().strip()]

def read_grid(r, c):
    grid = [read_row() for _ in range(r)]
    if any(len(row) != c for row in grid):
        raise ValueError('wrong shape while reading grid')
    log('START', repr(grid))
    return grid

def write_grid(grid):
    log('END', repr(grid))
    for row in grid:
        chars = ((EMPTY_SYMBOL if elem == 0 else BOMB_SYMBOL) for elem in row)
        print(''.join(chars))

def serialize(grid):
    return ''.join(map(str, chain.from_iterable(grid)))

def deserialize(state, r, c):
    assert len(state) == r * c, 'wrong shape while deserializing state'
    return [list(map(int, state[(i * c):((i + 1) * c)])) for i in range(r)]

r, c, n = map(int, input().split())
grid = read_grid(r, c)

def in_blast(i, j):
    return ((i != 0 and grid[i - 1][j] == 1)
         or (i != r - 1 and grid[i + 1][j] == 1)
         or (j != 0 and grid[i][j - 1] == 1)
         or (j != c - 1 and grid[i][j + 1] == 1))

def clear_blast_zones(): # removes non-bombs that are about to be destroyed
    for i in range(r):
        for j in range(c):
            if grid[i][j] > 1 and in_blast(i, j):
                grid[i][j] = 0

def count_down(): # reduces bomb timers by one tick, removing detonated bombs
    for row in grid:
        for j in range(c):
            if row[j] != 0:
                row[j] -= 1

def burn_fuses():
    clear_blast_zones()
    count_down()

def plant_bombs(): # plants bombs on empty squares
    for row in grid:
        for j in range(c):
            if row[j] == 0:
                row[j] = FUSE_TIME

states = [] # time => state (from beginning)
times = {}  # state => time (after initial steps)

def write_history(time, map_to_time=True): # always maps from time to state
    state = serialize(grid)
    assert len(states) == time
    states.append(state)

    if map_to_time:
        try:
            return times[state]
        except KeyError:
            times[state] = time

    return None

# the first two ticks differ from the others and must be manually entered
write_history(0, False)
burn_fuses()
write_history(1, False)

# the remaining ticks can be simulated automatically
for time in range(NORMAL_RULES_START, n + 1):
    burn_fuses()
    if time % PLANTING_PERIOD == 0:
        plant_bombs()

    old_time = write_history(time)
    if old_time is not None:
        state_period = time - old_time
        assert state_period > 0
        end_time = old_time + (n - old_time) % state_period
        assert NORMAL_RULES_START <= old_time <= end_time < time
        break
else:
    end_time = n

log('end_time =', end_time)

write_grid(deserialize(states[end_time], r, c))
