#!/usr/bin/env python3

DOMAIN = range(1, 13)

for i in DOMAIN:
    print(*(' %3d' % (i * j) for j in DOMAIN), sep = '')
