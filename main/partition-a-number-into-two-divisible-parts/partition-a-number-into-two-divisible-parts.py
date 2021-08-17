#!/usr/bin/env python3

def split_number(s, a, b):
    a = int(a)
    b = int(b)
    
    for i in range(1, len(s)):
        left = s[:i]
        right = s[i:]
        
        if int(left) % a == 0 and int(right) % b == 0:
            return [left, right]
    
    return ['-1']

for t in range(int(input())):
    print(*split_number(*input().split()))
