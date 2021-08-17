def get():
    return int(raw_input())

def get_words():
    count = get()
    words = raw_input().split()
    assert len(words) == count
    return words

for t in xrange(get()):
    ans = [False] * 10
    for i in (ord(digit) - ord('0') for num in get_words() for digit in num):
        ans[i] = True
    
    print ' '.join(str(i) for i in xrange(len(ans)) if ans[i])
