LENGTH = 10
PATTERN = re.compile(r'(?=(.{%d}).*?\1)' % LENGTH)


class Solution:
    def findRepeatedDnaSequences(self, s):
        """
        :type s: str
        :rtype: List[str]
        """
        starts = (match.start() for match in PATTERN.finditer(s))
        return list({s[index : index + LENGTH] for index in starts})
