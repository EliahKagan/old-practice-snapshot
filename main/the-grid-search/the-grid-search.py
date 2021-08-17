#!/usr/bin/env python3

import re
import sys

def read_row(width):
    line = sys.stdin.readline()
    if len(line) != (width + 1 if line[-1] == '\n' else width):
        raise ValueError('wrong length line in text/pattern')
    return line

def read_grid():
    height, width = map(int, input().split())
    return height, width, [read_row(width) for _ in range(height)]

def run():
    text_height, text_width, text_lines = read_grid()
    pattern_height, pattern_width, pattern_lines = read_grid()

    gap = text_width - pattern_width + 1 # add 1 for the newline
    if gap < 1:
        return False

    pattern = (r'.{%d}' % gap).join(line.rstrip() for line in pattern_lines)
    text = ''.join(text_lines)

    return re.search(pattern, text, re.S)

for _ in range(int(input())):
    print('YES' if run() else 'NO')
