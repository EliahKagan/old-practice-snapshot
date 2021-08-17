def get_one():
    return int(raw_input())

def get_many(count):
    values = map(int, raw_input().split())
    assert len(values) == count
    return values

for t in xrange(get_one()):
    n = get_one()
    assert n > 0

    a = sorted(set(get_many(n)))
    a.append(a[-1] + 2)

    print sum(1 for i in xrange(len(a) - 1) if a[i + 1] - a[i] != 1)
