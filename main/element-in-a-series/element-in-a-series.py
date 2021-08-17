#!/usr/bin/env python3

def get_val():
    return int(input())

def get_non_leading_bits(n):
    return bin(n)[3:]

DIGIT_MAP = {'0': '4', '1': '7'}

def generate_elements(nmax=1000):
    for i in range(1, nmax + 2):
        yield ''.join(DIGIT_MAP[c] for c in get_non_leading_bits(i))

ELEMS = list(generate_elements())

for _ in range(get_val()):
    print(ELEMS[get_val()])
