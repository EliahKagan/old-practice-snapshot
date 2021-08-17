from itertools import product

a = (map(int, raw_input().split()) for i in xrange(2))

for pair in product(*a):
    print pair,
