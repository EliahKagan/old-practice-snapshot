def input_set():
    n = int(raw_input())
    a = map(int, raw_input().split())
    return set(a)

print len(input_set() | input_set())
