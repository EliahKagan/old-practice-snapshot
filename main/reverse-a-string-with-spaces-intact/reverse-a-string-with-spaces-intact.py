#!/usr/bin/env python3

def read_text():
    return list(input().strip())

def print_text(s):
    print(''.join(s))

def skip_right(s, i):
    for j in range(i + 1, len(s)):
        if not s[j].isspace():
            return j
    
    return len(s)

def skip_left(s, i):
    for j in range(i - 1, -1, -1):
        if not s[j].isspace():
            return j;
    
    return -1

def reverse_around_whitespace(s):
    i = 0
    j = len(s) - 1
    while i < j:
        s[i], s[j] = s[j], s[i]
        i = skip_right(s, i)
        j = skip_left(s, j)

for _ in range(int(input())):
    s = read_text()
    reverse_around_whitespace(s)
    print_text(s)
