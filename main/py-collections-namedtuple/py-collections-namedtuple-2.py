from collections import namedtuple
n = int(input())
Record = namedtuple('Record', input())
print('{:.2f}'.format(sum(int(Record(*input().split()).MARKS) for _ in range(n)) / n))