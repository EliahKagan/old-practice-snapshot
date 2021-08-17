for t in xrange(0, int(raw_input())):
    n = int(raw_input())
    a = map(int, raw_input().split())
    assert n > 0 and len(a) == n
    
    count = 1
    maxval = a[0]
    
    for x in a:
        if maxval < x:
            maxval = x
            count += 1
    
    print count
