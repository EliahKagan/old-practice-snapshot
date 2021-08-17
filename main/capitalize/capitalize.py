def capitalize(string):
    a = list(string)
    
    for i in xrange(0, len(a)):
        if i == 0 or a[i - 1] == ' ':
            a[i] = a[i].capitalize()
    
    return ''.join(a)
