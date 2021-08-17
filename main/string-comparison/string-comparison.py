#!/usr/bin/env python3

import re

TOKEN_REGEX = re.compile(r'ng|[a-z]')
POSITION_OF_NG_TOKEN = ord('o')

def lex(text):
    '''Parses text greedily into lexical tokens that are 'ng' or a letter.'''
    return TOKEN_REGEX.findall(text)

def pos(tok):
    '''Finds tok's lexicographical position in the "native language."'''
    if len(tok) == 2:
        return POSITION_OF_NG_TOKEN
    
    ordinal = ord(tok)
    return ordinal if ordinal < POSITION_OF_NG_TOKEN else ordinal + 1

def posmap(text):
    '''Maps text to a list of lexicographical positions of its "letters."'''
    return list(map(pos, lex(text)))

def compare(lhs, rhs):
    '''Compares lhs and rhs lexicographically in the "native language."
    Returns -1 if lhs < rhs, 0 if lhs == rhs, and +1 if lhs > rhs.'''
    if lhs == rhs:
        return 0
    
    return -1 if posmap(lhs) < posmap(rhs) else 1

for _ in range(int(input())):
    print(compare(*input().split()))
