from collections import deque

def get_one():
    return int(raw_input())

def get_many():
    n = get_one()
    a = map(int, raw_input().split())
    assert len(a) == n > 0
    return deque(a, n)

def rotate_and_delete(q):
    for i in xrange(-1, -q.maxlen, -1):
        q.rotate(1)
        
        try:
            del q[i]
        except IndexError:
            q.popleft()
    
    return q.pop()

for t in xrange(get_one()):
    print rotate_and_delete(get_many())
