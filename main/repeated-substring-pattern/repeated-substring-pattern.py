PATTERN = re.compile(r'(.+)\1+')

class Solution:
    def repeatedSubstringPattern(self, s):
        """
        :type s: str
        :rtype: bool
        """
        return bool(PATTERN.fullmatch(s))
