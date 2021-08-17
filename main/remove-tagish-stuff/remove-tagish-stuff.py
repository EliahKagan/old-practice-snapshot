#!/usr/bin/env python3

import re
from sys import argv
from pathlib import Path

pattern = re.compile(r'</?[^\s/<>][^>]*>')

for path in argv[1:]:
    text = Path(path).read_text()
    print(pattern.sub('', text))
