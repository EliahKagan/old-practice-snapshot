#!/usr/bin/env python3

import re

SENTENCE = re.compile(r'[^.!?]+')
WORD = re.compile(r'[A-Za-z]+')

for t in range(int(input())):
    line = input()
    print(len(SENTENCE.findall(line)), len(WORD.findall(line)))
