for t in xrange(0, int(raw_input())):
    n = int(raw_input())
    a = map(int, raw_input().split())
    assert len(a) == n
    
    count = 0
    
    for i in xrange(0, n - 1):
        lhs = i * a[i]
        for j in xrange(i + 1, n):
            if lhs > j * a[j]:
                count += 1
    
    print count
