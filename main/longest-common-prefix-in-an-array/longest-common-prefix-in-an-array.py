#!/usr/bin/env python3

def get_longest_common_prefix(words):
    if len(words) == 0:
        return ''
    
    first = words[0]
    i = 0
    istop = min(len(w) for w in words)
    while i != istop and all(w[i] == first[i] for w in words):
        i += 1
    
    return first[:i]

for _ in range(int(input())):
    input() # don't need n
    prefix = get_longest_common_prefix(input().split())
    print('-1' if len(prefix) == 0 else prefix)
