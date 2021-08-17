#!/usr/bin/env python3

table = [[""], ["()"]]

def generateRowContents(n):
    '''Generates elements for the nth row of the table, provided that all
    previous rows have been fully generated and stored in the table.'''
    # We can concatenate entries whose lengths sum to n.
    for k in range(1, n):
        for s in table[n - k]:
            for t in table[k]:
                yield s + t

    # We can wrap entries, whose lengths are n - 1, in parentheses.
    for u in table[n - 1]:
        yield '(' + u + ')'


class Solution:
    def generateParenthesis(self, n):
        """
        :type n: int
        :rtype: List[str]
        """
        for i in range(len(table), n + 1):
            table.append(list(set(generateRowContents(i))))

        return table[n]
