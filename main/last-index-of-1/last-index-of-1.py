#!/usr/bin/env python3

def findLast(s, c):
    for i in range(len(s) - 1, -1, -1):
        if s[i] == c:
            return i
    
    return -1

for _ in range(int(input())):
    print(findLast(input().strip(), '1'))
