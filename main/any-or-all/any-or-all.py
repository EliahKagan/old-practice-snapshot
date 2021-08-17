input() # don't need n
a = input().split()
print(all(int(s) > 0 for s in a) and any(''.join(reversed(s)) == s for s in a))