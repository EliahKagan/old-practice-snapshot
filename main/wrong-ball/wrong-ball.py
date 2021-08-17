#!/usr/bin/env python3

wrongs = 'BR'

def count_wrongs(s):
    acc = 0
    
    for i in range(len(s)):
        if s[i] == wrongs[i % 2]:
            acc += 1
    
    return acc

for t in range(int(input())):
    print(count_wrongs(input().strip()))
