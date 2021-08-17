#!/usr/bin/env python3

def sum_substrings(s):
    acc = 0
    
    for i in range(len(s)):
        for j in range(i + 1, len(s) + 1):
            acc += int(s[i:j])
    
    return acc

for t in range(int(input())):
    print(sum_substrings(input().strip()))
