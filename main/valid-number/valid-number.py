PATTERN = re.compile(r'\s*[+-]?(?:\d+(?:\.\d*)?|\.\d+)(?:[Ee][+-]?\d+)?\s*')

class Solution:
    def isNumber(self, s):
        """
        :type s: str
        :rtype: bool
        """
        return bool(PATTERN.fullmatch(s))
