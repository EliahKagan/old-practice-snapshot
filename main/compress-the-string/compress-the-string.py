from itertools import groupby

for k, g in groupby(raw_input().strip()):
    print '({}, {})'.format(len(list(g)), k),
