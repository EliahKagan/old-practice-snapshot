#/usr/bin/env python3

def skip_sum(values, parity):
    assert 0 <= parity <= 1
    return sum(values[parity::2])

def zigzag_min(a, b):
    assert(len(a) == len(b))
    ab = skip_sum(a, 0) + skip_sum(b, 1)
    ba = skip_sum(b, 0) + skip_sum(a, 1)
    return min(ab, ba);

def read_record():
    return [int(tok) for tok in input().split()]

for t in range(int(input())):
    input() # don't need n
    print(zigzag_min(*(read_record() for _ in range(2))))
