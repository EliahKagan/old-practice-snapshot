#!/usr/bin/env python3

import collections
import re

def get_patterns():
    '''Returns (X can win regex, O can win regex).'''
    t = r'__\.|_\._|\.__|_.{4}_.{4}\.|_.{4}\..{4}_|\..{4}_.{4}_'
    return re.compile(t.replace('_', 'x')), re.compile(t.replace('_', 'o'))

X_CAN_WIN, O_CAN_WIN = get_patterns()

def count_x_o(board):
    c = collections.Counter(board)
    x, o = c['x'], c['o']
    assert 0 <= x - o <= 1
    return x, o

def next_can_win(board):
    x, o = count_x_o(board)
    return (X_CAN_WIN if x == o else O_CAN_WIN).search(board)

def read_board():
    return ' '.join(input().strip() for _ in range(4))

for _ in range(int(input())):
    print('YES' if next_can_win(read_board()) else 'NO')
