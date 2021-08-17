GROUPERS = {'(': ')', '{': '}', '[': ']'}

class Solution:
    def isValid(self, s):
        """
        :type s: str
        :rtype: bool
        """
        stack = []

        for c in s:
            try:             # try it as an opener
                stack.append(GROUPERS[c])
            except KeyError: # try it as a closer
                try:
                    if stack.pop() != c:
                        return False # invalid if unmatched
                except IndexError:
                    return False     # invalid if there's nothing to match

        return not stack # invalid if any more closers are needed
