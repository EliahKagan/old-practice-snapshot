def input_set():
    return set(map(int, raw_input().split()))

s = input_set()
print all(s > input_set() for i in xrange(0, int(raw_input())))
