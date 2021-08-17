#!/usr/bin/env python3

import re
from sys import argv
from pathlib import Path

start = re.compile(r'(?i)<html\s*>')
end = re.compile(r'(?i)</html\s*>')

for path in argv[1:]:
    text = Path(path).read_text()
    print(text[start.search(text).end() : end.search(text).start()].strip())
