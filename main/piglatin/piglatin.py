#!/usr/bin/env python

print 'Please input an ordinary single English word, in all lower-case.'
word = raw_input()

if not all(ch.islower() for ch in word):
    print "That don't seem lik no word to me!"
    exit(1)

print '%s%say' % (word[1:], word[0])
