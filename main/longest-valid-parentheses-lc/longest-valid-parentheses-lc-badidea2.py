class Solution:
    def longestValidParentheses(self, s):
        """
        :type s: str
        :rtype: int
        """
        best = cur = openers = 0

        for c in s:
            if c == '(':
                openers += 1
            elif c != ')':
                raise ValueError('invalid character in string')
            elif openers:
                openers -= 1
                cur += 2
            else:
                best = max(best, cur)
                openers = cur = 0



        return max(best, cur)
