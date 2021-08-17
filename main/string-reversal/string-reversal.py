for t in xrange(int(raw_input())):
    chars = set()
    rev = []
    
    for c in reversed(raw_input()):
        if not (c in chars or c.isspace()):
            chars.add(c)
            rev.append(c)
    
    print ''.join(rev)
