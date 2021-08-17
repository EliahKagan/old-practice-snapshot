#!/usr/bin/env python3

import numpy
import sys

FUSE_TIME = 3
NORMAL_RULES_START = 2
PLANTING_PERIOD = 2

if any(arg == '-v' or arg == '--verbose' for arg in sys.argv[1:]):
    def log(*values):
        print(sys.argv[0] + ':', *values, file=sys.stderr)
else:
    def log(*values):
        pass

def read_row():
    return [(FUSE_TIME if ch == 'O' else 0) for ch in input().strip()]

def read_grid(r, c):
    grid = numpy.array([read_row() for _ in range(r)])
    if grid.shape != (r, c):
        raise ValueError('wrong shape')
    return grid

def write_grid(grid):
    for row in grid:
        print(''.join(('.' if elem == 0 else 'O') for elem in row))

def serialize(grid):
    return ''.join(map(str, grid.ravel()))

def deserialize(state, r, c):
    return numpy.array(list(state), int).reshape(r, c)

r, c, n = map(int, input().split())
grid = read_grid(r, c)

def in_blast(i, j):
    return ((i != 0 and grid[i - 1][j] == 1)
         or (i != r - 1 and grid[i + 1][j] == 1)
         or (j != 0 and grid[i][j - 1] == 1)
         or (j != c - 1 and grid[i][j + 1] == 1))

def clear_blast_zones(): # removes destroyed objects *except* detonating bombs
    for i in range(r):
        for j in range(c):
            if grid[i][j] > 1 and in_blast(i, j):
                grid[i][j] = 0

def burn_fuses():
    clear_blast_zones() # remove non-bombs from blast zones of detonating bombs
    grid[grid > 0] -= 1 # remove detonated bombs; take others toward detonation

def plant_bombs(): # plants bombs on empty squares
    grid[grid == 0] = FUSE_TIME

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
