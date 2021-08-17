#!/usr/bin/env python

word = raw_input('Enter a word: ')

if len(word) > 0 and word.isalpha():
    word = word.lower()
    first = word[0]
    print word[1:] + word[0] + 'ay'
else:
    print 'empty'
