def gcd(m, n):
    return m if n == 0 else gcd(n, m % n)

def lcm(m, n):
    return m / gcd(m, n) * n

for t in xrange(0, int(raw_input())):
    raw_input() # don't need n
    print reduce(lcm, map(int, raw_input().split()))
