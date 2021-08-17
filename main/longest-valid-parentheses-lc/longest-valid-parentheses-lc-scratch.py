class Solution:
    def longestValidParentheses(self, s):
        """
        :type s: str
        :rtype: int
        """
        d = [0] * len(s)

        for i in range(1, len(s)):
            if s[i - 1] == '(' and s[i] == ')':
                d[i] = 1

        for i in range(2, len(s)):
            if s[i] != ')':
                continue

            # nesting
            if s[i - 1] == ')':
