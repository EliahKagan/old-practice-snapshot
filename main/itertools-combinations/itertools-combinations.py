from itertools import combinations

a = raw_input().split()
letters = sorted(a[0])
max_length = int(a[1])

for length in xrange(1, max_length + 1):
    for co in combinations(letters, length):
        print ''.join(co)
