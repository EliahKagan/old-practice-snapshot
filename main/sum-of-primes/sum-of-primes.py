PRIME_DIGITS = {'2': 2, '3': 3, '5': 5, '7':7}

for t in xrange(0, int(raw_input())):
    print sum(PRIME_DIGITS.get(d, 0) for d in raw_input())
