#!/usr/bin/env python3

import re
from sys import argv
from pathlib import Path

tag = re.compile(r'</?[^\s/<>][^>]*>')
excess = re.compile('\n{3,}')


for path in argv[1:]:
    text = Path(path).read_text()
    detagged = tag.sub('', text)
    print(excess.sub('\n\n', detagged).strip())
