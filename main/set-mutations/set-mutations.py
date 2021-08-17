def lex():
    return raw_input().split()

def input_set(size):
    a = map(int, lex())
    assert len(a) == int(size)
    return set(a)

def input_query():
    cmd, size = lex()
    return cmd.strip(), input_set(size)

s = input_set(raw_input())

for i in xrange(0, int(raw_input())):
    cmd, t = input_query()
    if cmd == 'update':
        s |= t
    elif cmd == 'intersection_update':
        s &= t
    elif cmd == 'difference_update':
        s -= t
    elif cmd == 'symmetric_difference_update':
        s ^= t

print sum(s)
