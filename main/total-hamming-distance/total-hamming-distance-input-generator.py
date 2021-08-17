#!/usr/bin/env python3

from random import randint

a = 0
b = 10**9

print(', '.join(str(randint(a, b)) for _ in range(10**4)))
