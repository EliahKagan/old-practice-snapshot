#!/usr/bin/env python

def getval():
    try:
        print
        n = int(raw_input('> '))
        return n if n > 0 else None
    except ValueError:
        return None

def show_nines(n):
    while True:
        digits = str(n)
        n = int(digits[0])
        print digits[0],
        
        for d in digits[1:]:
            n += int(d)
            print '+', d,
        
        print '=', n
        
        if len(digits) == 1:
            break

print 'Enter a positive integer (or anything else to quit).'

while True:
    n = getval()
    
    if n == None:
        break
    
    if n % 9 != 0:
        print n, "isn't divisible by 9."
        continue
    
    show_nines(n)
