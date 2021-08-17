#!/usr/bin/env python3

import re

def build_subseq_re(pattern):
    return ''.join(r'[^{0}]*{0}'.format(c) for c in pattern) + '.*'

def is_subseq(pattern, text):
    return re.fullmatch(build_subseq_re(pattern), text)

for t in range(int(input())):
    print('1' if is_subseq(*input().split()) else '0')
