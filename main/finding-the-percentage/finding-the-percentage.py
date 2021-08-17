marks = {}

for i in xrange(0, int(raw_input())):
    row = raw_input().split()
    marks[row[0]] = map(float, row[1:])

result = marks[raw_input().strip()]
print '{0:.2f}'.format(sum(result) / len(result))
