#!/usr/bin/env python3

def magic(c):
    return chr(ord('z') - ord(c) + ord('a'))

for t in range(int(input())):
    print(''.join(map(magic, input().strip())))
