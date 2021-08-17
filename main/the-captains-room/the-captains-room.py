from collections import Counter

raw_input() # ignore k
print Counter(map(int, raw_input().split())).most_common()[-1][0]
