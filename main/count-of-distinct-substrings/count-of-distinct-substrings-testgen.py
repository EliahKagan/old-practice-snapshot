#!/usr/bin/env python3

from random import randint

COUNT = 50
LENGTH = 1000

LOW = ord('a')
HIGH = ord('z')

print(COUNT)
for _ in range(COUNT):
    print(''.join(chr(randint(LOW, HIGH)) for _ in range(LENGTH)))
