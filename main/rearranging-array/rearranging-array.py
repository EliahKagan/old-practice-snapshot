for t in xrange(0, int(raw_input())):
    n = int(raw_input())
    a = sorted(map(int, raw_input().split()))
    
    for i in xrange(0, n / 2):
        print a[i], a[n - 1 - i],
    
    if n % 2 == 0:
        print
    else:
        print a[n / 2]
