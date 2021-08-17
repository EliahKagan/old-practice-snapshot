NOT_FOUND = -1
BASE = 10

def gcd(m, n):
    return m if n == 0 else gcd(n, m % n)
    
for t in xrange(int(raw_input())):
    decimal_repr = raw_input().strip()
    point_index = decimal_repr.rfind('.')
    
    if point_index == NOT_FOUND:
        print 1
        continue
    
    numerator = int(decimal_repr[:point_index]
                    + decimal_repr[(point_index + 1):])
                    
    denominator = BASE**(len(decimal_repr) - point_index - 1)
    
    print denominator / gcd(numerator, denominator)
