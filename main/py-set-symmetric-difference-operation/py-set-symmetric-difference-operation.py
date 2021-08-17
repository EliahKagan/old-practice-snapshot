def input_set():
    raw_input() # ignore n
    return set(map(int, raw_input().split()))

print len(input_set() ^ input_set())
