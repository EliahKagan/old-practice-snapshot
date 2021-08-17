def input_set():
    n = int(raw_input())
    a = map(int, raw_input().split())
    assert len(a) == n
    return set(a)

for x in sorted(input_set() ^ input_set()):
    print x
