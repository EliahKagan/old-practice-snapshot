#!/usr/bin/env python3

def read_val():
    return int(input())

def read_record():
    return list(map(int, input().split()))

def get_ranks(scores):
    for _, idx in sorted((-score, idx) for idx, score in enumerate(scores)):
        yield idx

def get_top_ranks(scores, distinct_count):
    ranked_scores = set()

    for rank in get_ranks(scores):
        ranked_scores.add(scores[rank])
        if len(ranked_scores) > distinct_count:
            break
        yield rank

for _ in range(read_val()):
    input() # don't need n
    scores = read_record()
    distinct_count = read_val()
    print(*get_top_ranks(scores, distinct_count))
