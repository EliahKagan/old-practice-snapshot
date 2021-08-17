#!/usr/bin/env python3

import re

VOWEL = re.compile(r'[aeiou]', re.I)

def fold_vowels(word):
    return VOWEL.sub('a', word)
