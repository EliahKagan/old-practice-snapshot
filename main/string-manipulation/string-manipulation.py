def get():
    return int(raw_input())

def get_words():
    n = get()
    a = raw_input().split()
    assert len(a) == n
    return a

for t in xrange(get()):
    ws = [None]  # word stack, containing None as start mark
    
    for w in get_words():
        if w == ws[-1]:
            del ws[-1]
        else:
            ws.append(w)
    
    print len(ws) - 1
