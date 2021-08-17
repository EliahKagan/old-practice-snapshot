#!/usr/bin/env python3

import re

PATTERN = re.compile(r'(?:a(?:da)+)+')

def seperate_noise(message):
    indices = [0]
    noise_bursts = []

    for sre_match in PATTERN.finditer(message):
        indices.append(sre_match.start())
        indices.append(sre_match.end())
        noise_bursts.append(sre_match.group(0))

    indices.append(len(message))

    index_range = range(0, len(indices), 2)
    signal = ''.join(message[indices[i]:indices[i + 1]] for i in index_range)

    return signal, ''.join(noise_bursts)

for _ in range(int(input())):
    signal, noise = seperate_noise(input().strip())
    print(signal + noise)
