class Solution:
    def simplifyPath(self, path):
        """
        :type path: str
        :rtype: str
        """
        res = []

        for name in path.split('/'):
            if not name or name == '.':
                pass
            elif name == '..':
                try:
                    del res[-1]
                except IndexError:
                    pass
            else:
                res.append(name)

        return '/' + '/'.join(res)
