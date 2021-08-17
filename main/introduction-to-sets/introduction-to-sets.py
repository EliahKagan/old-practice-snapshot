n = int(raw_input())
a = map(int, raw_input().split())
assert len(a) == n

s = set(a)
print float(sum(s)) / len(s)
