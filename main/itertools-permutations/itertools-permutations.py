from itertools import permutations

a = raw_input().split()
for p in permutations(sorted(a[0]), int(a[1])):
    print ''.join(p)
