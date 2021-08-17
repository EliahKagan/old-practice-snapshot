m = int(raw_input())
a = map(int, raw_input().split())
assert len(a) == m
s = set(a)

for i in xrange(0, int(raw_input())):
    q = raw_input().split()
    if q[0] == 'pop':
        assert len(q) == 1
        s.pop()
    elif q[0] == 'remove':
        assert len(q) == 2
        s.remove(int(q[1]))
    elif q[0] == 'discard':
        assert len(q) == 2
        s.discard(int(q[1]))
    else:
        assert not 'unrecognized command'

print sum(s)
