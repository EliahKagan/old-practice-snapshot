def get():
    return int(raw_input())

def get_many():
    n = get()
    a = map(int, raw_input().split())
    assert len(a) == n
    return a

for t in xrange(get()):
    a = []
    b = []
    
    for x in get_many():
        (b if x < 0 else a).append(x)
    
    if len(a) == 0 or len(b) == 0:
        print
    else:
        print ' '.join(map(str, a + b))
