#!/usr/bin/env python3

import sys

status = 0

for path in sys.argv[1:]:
    try:
        with open(path) as f:
            lines = words = chars = 0

            for line in f:
                lines += 1
                words += len(line.split())
                chars += len(line) + 1

            print('%s: %d %d %d' % (path, lines, words, chars))
    except IOError as e:
        print('%s: error: %s: %s' % (sys.argv[0], e.filename, e.strerror))
        status = 1

sys.exit(status)
