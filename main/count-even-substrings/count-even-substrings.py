#!/usr/bin/env python3

def count_even_substrings(s):
    return sum(i + 1 for i in range(len(s)) if s[i] in '02468')

for t in range(int(input())):
    print(count_even_substrings(input().strip()))
