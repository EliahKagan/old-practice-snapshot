def get_one():
    return int(raw_input())

def get_many(count):
    values = map(int, raw_input().split())
    assert len(values) == count
    return values

for t in xrange(get_one()):
    n = get_one()
    a = sorted(get_many(n))
    b = sorted(get_many(n), reverse = True)
    print sum(a[i] * b[i] for i in xrange(n))
