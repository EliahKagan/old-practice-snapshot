#!/usr/bin/env python3

vowels = set('aeiou')

for t in range(int(input())):
    distinct = len(set(input().strip()) - vowels)
    print('SHE!' if distinct % 2 == 0 else 'HE!')
