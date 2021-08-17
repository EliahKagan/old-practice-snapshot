#!/usr/bin/env python3

import collections

ledger = collections.OrderedDict()

for _ in range(int(input())):
    name, _, price_str = input().rpartition(' ')
    price = int(price_str)
    try:
        ledger[name] += price
    except KeyError:
        ledger[name] = price

for name, net_price in ledger.items():
    print(name, net_price)
