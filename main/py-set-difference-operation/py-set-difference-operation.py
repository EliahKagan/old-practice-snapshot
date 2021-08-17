def input_set():
    raw_input() # ignore n
    return set(map(int, raw_input().split()))

english = input_set()
french = input_set()

print len(english - french)
