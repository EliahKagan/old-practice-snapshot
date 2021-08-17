#!/usr/bin/env python3

from collections import defaultdict

def get_char_counts(s):
    cnt = defaultdict(int)
    
    for c in s:
        cnt[c] += 1
    
    return cnt

def equal_point(s):
    cnt = get_char_counts(s)
    
    for i, c in enumerate(range(len(s))):
        cnt[c] -= 1
        if cnt['('] == cnt[')']:
            return i + 1
    
    return -1

for _ in range(int(input())):
    print(equal_point(input().strip()))
