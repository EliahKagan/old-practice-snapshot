import re

r = re.compile(r'[^h]*h[^e]*e[^l]*l[^l]*l[^o]*o.*')

for t in range(int(input())):
    print('1' if r.fullmatch(input().strip()) else '0')
