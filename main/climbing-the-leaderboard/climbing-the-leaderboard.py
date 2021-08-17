#!/usr/bin/env python3

def read_record():
    input() # don't need n or m
    return map(int, input().split())

def drop_consecutive_dupes(values):
    prev = None
    for cur in values:
        if prev != cur:
            yield cur
            prev = cur

board = list(drop_consecutive_dupes(read_record()))
rank = len(board) # zero-based

for score in read_record():
    while rank != 0 and board[rank - 1] <= score:
        rank -= 1
    print(rank + 1) # so that it is one-based
