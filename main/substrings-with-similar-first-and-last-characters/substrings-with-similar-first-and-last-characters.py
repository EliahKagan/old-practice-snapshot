#!/usr/bin/env python3

A = ord('a')

def count_same_ended_substrings(s):
    freqs = [0] * 26
    for c in s:
        freqs[ord(c) - A] += 1
    
    return sum(k * (k + 1) // 2 for k in freqs)

for t in range(int(input())):
    input() # don't need n
    print(count_same_ended_substrings(input().strip()))
