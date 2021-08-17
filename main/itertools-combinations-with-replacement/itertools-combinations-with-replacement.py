from itertools import combinations_with_replacement

a = raw_input().split()
for co in combinations_with_replacement(sorted(a[0]), int(a[1])):
    print ''.join(co)
