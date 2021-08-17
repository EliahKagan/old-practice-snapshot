def minion_game(string):
    vowels = set('AEIOU')
    kevin = stuart = 0
    n = len(string)
    
    for i in xrange(n):
        j = n - i
        if string[i] in vowels:
            kevin += j
        else:
            stuart += j
    
    if kevin == stuart:
        print 'Draw'
    elif kevin < stuart:
        print 'Stuart', stuart
    else:
        print 'Kevin', kevin
