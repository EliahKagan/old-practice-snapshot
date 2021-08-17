#!/usr/bin/env python3

from collections import Counter

key_freqs = Counter()
freq_freqs = Counter()

def insert(key):
    '''Inserts an occurence key into the data structure.'''
    freq = key_freqs[key]
    if freq:
        freq_freqs[freq] -= 1
    
    freq += 1
    freq_freqs[freq] += 1
    key_freqs[key] = freq

def delete(key):
    '''Deletes an occurrence of key from the data structure, if present.'''
    freq = key_freqs[key]
    if not freq:
        return
    
    freq_freqs[freq] -= 1
    
    freq -= 1
    if freq:
        freq_freqs[freq] += 1
    
    key_freqs[key] = freq

def check_freq(freq):
    '''Reports whether one of the current key frequencies is equal to freq.'''
    print(1 if freq_freqs[freq] else 0)

ACTIONS = [None, insert, delete, check_freq]

for _ in range(int(input())):
    action_index, key_or_freq = map(int, input().split())
    ACTIONS[action_index](key_or_freq)
