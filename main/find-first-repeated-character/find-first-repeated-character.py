#!/usr/bin/env python3

def get_first_rep(s):
    cs = set()
    
    for c in s:
        if c in cs:
            return c
        
        cs.add(c)
    
    return '-1'

for t in range(int(input())):
    print(get_first_rep(input().strip()))
