def distinct(s):
    a = []
    cs = set()
    
    for c in s:
        if c not in cs:
            cs.add(c)
            a.append(c)
    
    return ''.join(a)

def merge_the_tools(s, k):
    for row in (s[i:(i + k)] for i in xrange(0, len(s), k)):
        print distinct(row)
