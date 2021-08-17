def input_set():
    raw_input() # ignore n, since it's wrong in test cases 3, 4, and 5!
    return set(map(int, raw_input().split()))

print len(input_set() | input_set())
