from itertools import ifilter

def even(d):
    return int(d) % 2 == 0

for t in xrange(0, int(raw_input())):
    a = sorted(raw_input().strip(), reverse = True)
    
    irange = xrange(len(a) - 1, -1, -1)
    
    def even_at(i):
        return int(a[i]) % 2 == 0
    
    i = next(ifilter(even_at, irange), None)
    
    if i is not None:
        a.append(a.pop(i))
    
    print "".join(a)
