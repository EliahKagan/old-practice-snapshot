def input_val():
    return int(raw_input())

def input_row():
    return map(int, raw_input().split())

for t in xrange(input_val()):
    n = input_val()
    a = sorted(input_row())
    i, j = input_row()
    #assert 0 < i < j <= n == len(a)
    
    print sum(a[k] for k in xrange(i, j - 1))
