N, M = map(int,raw_input().split()) # More than 6 lines of code will result in 0 score. Blank lines are not counted.
for i in xrange(1,N,2): 
    print ('.' + '..'.join(['|'] * i) + '.').center(N * 3, '-')
print 'WELCOME'.center(N * 3, '-')
for i in xrange(N-2,-1,-2): 
    print ('.' + '..'.join(['|'] * i) + '.').center(N * 3, '-')
