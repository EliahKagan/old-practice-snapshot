class Solution:
    def judgeCircle(self, moves):
        """
        :type moves: str
        :rtype: bool
        """
        cnt = collections.Counter(moves)
        return cnt['U'] == cnt['D'] and cnt['L'] == cnt['R']
