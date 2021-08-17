#!/usr/bin/env python3

from functools import reduce
from operator import mul

def read_record():
    return map(int, input().split())

for _ in range(int(input())):
    _, k = read_record() # don't need n
    print(reduce(mul, sorted(read_record(), reverse=True)[:k]))
