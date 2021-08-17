#!/usr/bin/env python3

import collections
import re

splitter = re.compile(r'\s+(?=\S+$)')
ledger = collections.OrderedDict()

for _ in range(int(input())):
    name, price_str = splitter.split(input())
    price = int(price_str)
    try:
        ledger[name] += price
    except KeyError:
        ledger[name] = price

for name, net_price in ledger.items():
    print(name, net_price)
